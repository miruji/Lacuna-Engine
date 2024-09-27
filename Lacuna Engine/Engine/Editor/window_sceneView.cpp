#include "Editor.h"

void LE::Editor::window_sceneView()
{
    if (!firstHudDraw) // first draw
    {
        ImGuiID MainID_Central = ImGui::DockBuilderGetCentralNode(backgroundDockSpace)->ID;
        ImGui::SetNextWindowDockID(MainID_Central);
    }
    //
    ImGui::Begin("Scene View", NULL, ImGuiWindowFlags_MenuBar);
        
        // -- game render top editor
        if (ImGui::BeginMenuBar())
        {
            if (menuItemImage("##sceneEditor_Move", "editor_move", "Move"))
            {
                std::cout << "EditorMove" << std::endl;
            }
            if (menuItemImage("##sceneEditor_Rotate", "editor_rotate", "Rotate"))
            {
                std::cout << "EditorRotate" << std::endl;
            }
            if (menuItemImage("##sceneEditor_Scale", "editor_scale", "Scale"))
            {
                std::cout << "EditorScale" << std::endl;
            }

            ImGui::EndMenuBar();
        }
        // -- render
        ImVec2 render_size = ImGui::GetWindowSize();
        ImVec2 render_pos = ImGui::GetCursorPos();
            // S.C.W & S.C.H fix
            float ratio;
            float imageW = render_size.x;
            float imageH = render_size.y;
            if (scene_started)
            {
                Scene& s = scene_manager.getCurrentScene();
                ratio  = render_size.x/ s.c[s.cCurrent].w;
                imageW = ratio * s.c[s.cCurrent].w;
                imageH = ratio * s.c[s.cCurrent].h;
            }
            imageW -= 11;
            imageH -= 53;
        Scene& s = scene_manager.getCurrentScene();
        //if (SceneStarted)
        if (false)
        {
            // ------------------ frame info
            if (ImGui::BeginChild("##sceneEditor_info", ImVec2(imageW, imageH), false))
            {
                if (scene_manager.getScenesSize())
                    ImGui::Text(("Current Scene: Num: [0], Name: ["+ scene_manager.getScene(0).name+"]").c_str()); // test text

                if (ImGui::IsWindowHovered())
                {
                    if (mouse_x >= 0) mouse_x = ImGui::GetMousePos().x-ImGui::GetWindowPos().x;
                    if (mouse_y >= 0) mouse_y = ImGui::GetMousePos().y-ImGui::GetWindowPos().y;
                }

                ImVec2 mouseXYPos = ImGui::GetCursorPos();

                int mouse_xx = mouse_x;
                if (mouse_xx < 0) mouse_xx = 0;
                int mouse_yy = mouse_y;
                if (mouse_yy < 0) mouse_yy = 0;

                const char* MouseXY = ("Mouse X: "+std::to_string(mouse_xx)+"; Mouse Y: "+std::to_string(mouse_yy)+" | ").c_str();
                ImGui::Text( MouseXY );

                ImGui::SetCursorPos( ImVec2(mouseXYPos.x+ImGui::CalcTextSize(MouseXY, NULL, true).x, mouseXYPos.y) );
                const char* CameraXY = ("Camera X: "+std::to_string(-int(s.c[s.cCurrent].x))+"; Camera Y: "+std::to_string(-int(s.c[s.cCurrent].y))).c_str();
                ImGui::Text( CameraXY );

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

                ImGui::EndChild();
            }
            // ------------------ draw frame
            render_size = ImVec2(s.c[s.cCurrent].w*2, s.c[s.cCurrent].h*2);//ImGui::GetWindowSize();
            //glViewport((S.C.X/2)+(-RenderSize.x/2), (S.C.Y/2)+(-RenderSize.y/2), RenderSize.x, RenderSize.y); // TO:DO: Camera
            //glViewport((-RenderSize.x/2),(-RenderSize.y/2),RenderSize.x,RenderSize.y);
            glViewport((-render_size.x/2), (-render_size.y/2), render_size.x, render_size.y);

            /* // projection
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(XY_TO_FLOAT(S.C.X, S.C.Y, RenderSize.x, RenderSize.y), 0);
            */
            /* // scale
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            float scale = 1;
            glOrtho(-scale, scale, -scale, scale, -10, 10);
            */
            // =========================================
            glBindFramebuffer(GL_FRAMEBUFFER, s.fbo);

                glBindTexture(GL_TEXTURE_2D, s.fboTexture);
                    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (S.C.X/2)+RenderSize.x/2, (S.C.Y/2)+RenderSize.y/2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (render_size.x/2), (render_size.y/2), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
                glBindTexture(GL_TEXTURE_2D, 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s.fboTexture, 0);
                    
                glBegin(GL_POLYGON); // bg TO:DO: Clear
                    glColor3f(0.1f, 0.3f, 0.3f);
                    glVertex2f(0, 0);
                    glVertex2f(0, 1.0f);
                    glVertex2f(1.0f, 1.0f);
                    glVertex2f(1.0f, 0);
                glEnd();

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                s.states[0]->func("Draw"); // draw scene

                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                    l.push("e", "Couldn't create frame buffer");
                
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // ------------------
            ImGui::SetCursorPosY(render_pos.y);
            ImGui::GetWindowDrawList()->AddImage(
                (void *)s.fboTexture, ImVec2(ImGui::GetCursorScreenPos()),
                ImVec2(ImGui::GetCursorScreenPos().x+imageW, ImGui::GetCursorScreenPos().y+imageH), ImVec2(0, 0), ImVec2(1, 1));
        }
    ImGui::End();
}