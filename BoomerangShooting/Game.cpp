//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "GameBase/Screen.h"
#include "Game/Scene/SceneManager.h"
#include "GameBase/GameResources.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    :
    m_deviceResources{},
    m_timer{},
    m_commonStates{},
    m_debugString{},
    m_inputManager{},
    m_sceneManager{}
    ,m_fullScreen{false}
    ,m_fadeManager{}
    ,m_soundManager{}
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    // デバイスリソース関連を設定する
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();



    // デバイスとコンテキストを取得する
    auto device  = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // 入力マネージャを作成する
    m_inputManager = std::make_unique<mylib::InputManager>(window);

    // コモンステートを作成する
    m_commonStates = std::make_unique<CommonStates>(device);
       

    // デバッグ文字列を作成する
    m_debugString = std::make_unique<mylib::DebugString>(
        device,
        context,
        L"Resources/Fonts/SegoeUI_18.spritefont"
    );


    // シーンへ渡す共通リソースを設定する
    CommonResources::GetInstance()->Initialize(
        &m_timer,
        m_deviceResources.get(),
        m_commonStates.get(),
        m_debugString.get(),
        m_inputManager.get()
    );


    // シーンマネージャを初期化する
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->Initialize();


    m_fadeManager = FadeManager::GetInstance();

    m_soundManager = SoundManager::GetInstance();

    //画像の読み込み　コンストラクタを呼ぶ
    GameResources::GetInstance();

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.

    // 入力マネージャを更新する
    m_inputManager->Update();

    // キーボードステートを取得する
    const auto& keyboardState = m_inputManager->GetKeyboardState();

    // 「ECS」キーで終了する
    if (keyboardState.Escape)
    {
        ExitGame();
    }


    // シーンマネージャを更新する
    m_sceneManager->Update(elapsedTime);

    m_soundManager->Update();

    m_fadeManager->Update(elapsedTime);

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.

    UNREFERENCED_PARAMETER(context);

    // デバッグ文字列を作成する：FPS
    //m_debugString->AddString("fps : %d", m_timer.GetFramesPerSecond());

    // シーンマネージャを描画する
    m_sceneManager->Render();

    m_fadeManager->Render();

    // デバッグ文字列を描画する
    m_debugString->Render(m_commonStates.get());

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);

    // ★追記
    BOOL fullScreen = FALSE;

    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullScreen, nullptr);

    if (m_fullScreen != fullScreen)
    {
        m_fullScreen = fullScreen;
        m_deviceResources->CreateWindowSizeDependentResources();
    }

}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width   = Screen::WIDTH;    // ★変更::800->Screen::WIDTH
    height  = Screen::HEIGHT;   // ★変更::600->Screen::HEIGHT
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    // ★追記★
    UNREFERENCED_PARAMETER(device);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
