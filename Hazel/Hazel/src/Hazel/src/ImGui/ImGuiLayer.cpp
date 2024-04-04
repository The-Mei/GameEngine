#include "hzpch.h"

#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
// #include "ImGuiOpenGLRenderer.h"
// #define IMGUI_IMPL_API
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "Application.h"

#include "GL/Gl.h"

namespace Hazel
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::onAttach()
    {
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();

        // ImGuiIO &io = ImGui::GetIO();
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        // io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        // io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        // io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        // io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        // io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        // io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        // io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        // io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        // io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        // io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        // io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        // io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        // io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        // io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        // io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        // io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        // io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        // io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        // io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        // io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        // io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        // ImGui_ImplOpenGL3_Init("#version 410");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
        // io.ConfigViewportsNoAutoMerge = true;
        // io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application &app = Application::get();
        GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGuiIO &io = ImGui::GetIO();

        Application &app = Application::get();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
    // void ImGuiLayer::onUpdate()
    // {

    //     ImGuiIO &io = ImGui::GetIO();
    //     Application &app = Application::get();
    //     io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    //     float time = (float)glfwGetTime();
    //     io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
    //     mTime = time;

    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui::NewFrame();

    //     static bool show = true;
    //     ImGui::ShowDemoWindow(&show);

    //     ImGui::Render();
    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // }

    // void ImGuiLayer::onEvent(Event &event)
    // {
    //     EventDispatcher dispatcher(event);
    //     dispatcher.dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
    //     dispatcher.dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
    //     dispatcher.dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
    //     dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
    //     dispatcher.dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
    //     dispatcher.dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
    //     dispatcher.dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
    //     dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::onWindowResizedEvent));
    // }

    // bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.MouseDown[e.getMouseButton()] = true;
    //     return false;
    // }

    // bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.MouseDown[e.getMouseButton()] = false;
    //     return false;
    // }

    // bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.MousePos = ImVec2(e.getX(), e.getY());
    //     return false;
    // }

    // bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.MouseWheelH += e.getXOffset();
    //     io.MouseWheel += e.getYOffset();
    //     return false;
    // }

    // bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.KeysDown[e.getKeyCode()] = true;
    //     io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    //     io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    //     io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    //     io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    //     return false;
    // }

    // bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.KeysDown[e.getKeyCode()] = false;
    //     return false;
    // }

    // bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     int keyCode = e.getKeyCode();
    //     if (keyCode > 0 && keyCode < 0x10000)
    //         io.AddInputCharacter((unsigned short)keyCode);
    //     return false;
    // }

    // bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent &e)
    // {
    //     ImGuiIO &io = ImGui::GetIO();
    //     io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
    //     io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //     glViewport(0, 0, e.getWidth(), e.getHeight());
    //     return false;
    // }
}