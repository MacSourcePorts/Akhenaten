#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "widget/debug_console.h"
#include "graphics/imagepak_holder.h"

#include "dev/debug.h"

ANK_REGISTER_PROPS_ITERATOR(dev_sprite_tool);

bool game_debug_show_properties_object(imagepak_handle ipak) {
    ImGui::PushID(0x82000000 | ipak.id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx((void*)ipak.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen, "%s", ipak.name.c_str());
    ImGui::TableSetColumnIndex(1);

    bool go = true;
    if (common_open) {
        const auto &names = ipak.handle->names();
        const auto &ids = ipak.handle->image_ids(); 
        for (int i = 0, size = names.size(); i < size && go; ++i) {
            ImGui::PushID(0x83000000 + i);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            image_t* img = const_cast<image_t*>(image_get(image_desc{ipak.id, i, 0}));
            bool anim_open = ImGui::TreeNodeEx(img, ImGuiTreeNodeFlags_DefaultOpen, "%s", img->bmp.name.c_str());
            ImGui::TableSetColumnIndex(1);

            const int ioffset = ids[i];

            if (anim_open) {
                if (img && img->atlas.p_atlas) {
                    ImGui::PushID(0x88000000 + i);
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::AlignTextToFramePadding();
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                    ImGui::TreeNodeEx("Field", flags, "Image");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::SetNextItemWidth(-FLT_MIN);

                    ImGui::Text("id:%d", ipak.id);
                    ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::Text(e_pack_type_tokens.name((e_pack)ipak.id));
                    ImGui::SameLine(); ImGui::Text("index:%d", ipak.index);
                    ImGui::SameLine(); ImGui::Text("i_offset:%d", ioffset);
                    int item_current = img->debug.animate;
                    pcstr animate_mode[] = { "None", "Figure" };
                    ImGui::SameLine(); ImGui::Text("mode"); ImGui::SameLine(); ImGui::SetNextItemWidth(100); ImGui::Combo("##animate", &item_current, animate_mode, std::size(animate_mode));
                    img->debug.animate = item_current;
                    ImGui::SameLine(); ImGui::Text("sprites:%d", img->animation.num_sprites);
                    ImGui::SameLine(); ImGui::Text("max_frame"); ImGui::SetNextItemWidth(30); ImGui::SameLine(); ImGui::InputScalar("##max_frame", ImGuiDataType_U8, (void *)&img->debug.max_frame);
                    ImGui::SameLine(); ImGui::Text("frame:%d", img->debug.frame);

                    const vec2i tx_offset = img->atlas.offset;
                    ImGui::SameLine(); ImGui::Text("offset:%d, %d", tx_offset.x, tx_offset.y);

                    auto drawImage = [] (image_t *img, int idx) {
                        if (img->mirrored_img != 0) {
                            img = img->mirrored_img;
                        }
                        const vec2i tx_offset = img->atlas.offset;
                        const vec2i atlas_size(img->atlas.p_atlas->width, img->atlas.p_atlas->height);
                        ImVec2 uv_min(tx_offset.x / (float)atlas_size.x, tx_offset.y / (float)atlas_size.y);
                        ImVec2 uv_max((tx_offset.x + img->width) / (float)atlas_size.x, (tx_offset.y + img->height) / (float)atlas_size.y);
                        const int ww = (img->width < 64 ? 64 : img->width);
                        const int wh = (img->height < 64 ? 64 : img->height);
                        ImGui::BeginChild(bstring32("##imageframe%d", idx), ImVec2(ww, wh), true);
                        ImGui::Image(img->atlas.p_atlas->texture, ImVec2(img->width, img->height), uv_min, uv_max);
                        ImGui::EndChild();
                    };

                    if (img->debug.animate == 1) {
                        static uint8_t animate_duration = 4;
                        ImGui::Text("duration"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputScalar("##duration", ImGuiDataType_U8, (void *)&animate_duration);
                        for (int dir = 0; dir < 8; ++dir) {
                            image_t *animg = const_cast<image_t *>(image_get(image_desc{ ipak.id, i, img->debug.frame * 8 + dir }));
                            drawImage(animg, dir);
                            ImGui::SameLine();
                        }

                        const int max_frame = (img->debug.max_frame == 0xff) ? 12 : img->debug.max_frame;
                        ++img->debug.frame_tick;
                        if (img->debug.frame_tick > animate_duration) {
                            img->debug.frame_tick = 0;
                            ++img->debug.frame;
                            if (img->debug.frame >= max_frame) {
                                img->debug.frame = 0;
                            }
                        }
                    } else {
                        drawImage(img, 0);
                    }

                    ImGui::NextColumn();
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
    return false;
}


void dev_sprite_tool(bool header) {
    static bool _debug_sprites_open = false;

    if (header) {
        ImGui::Checkbox("Sprites", &_debug_sprites_open);
        return;
    } 

    if (_debug_sprites_open && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        for (const auto &imgpak : g_image_data->common) {
            if (imgpak.name.empty()) {
                continue;
            }

            const bool stop = game_debug_show_properties_object(imgpak);
            if (stop) {
                break;
            }
        }
        ImGui::EndTable();
    }
}