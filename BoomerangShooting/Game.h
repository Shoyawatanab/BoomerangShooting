//
// Game.h
//

#pragma once

#include"GameBase/Common/DeviceResources.h"
#include"GameBase/Common/StepTimer.h"

// ★includeの追記★
#include "GameBase/Common/Commons.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Fade/FadeManager.h"
#include "GameBase/Manager/SoundManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;


    // ★追記ココから↓↓↓★

    // コモンステート
    std::unique_ptr<DirectX::CommonStates>  m_commonStates;


    // デバッグストリング
    std::unique_ptr<mylib::DebugString>     m_debugString;

    // 入力マネージャ
    std::unique_ptr<mylib::InputManager>    m_inputManager;

    // シーンマネージャ
    std::unique_ptr<SceneManager>           m_sceneManager;


    //フェードマネージャー
    FadeManager* m_fadeManager;
    //サウンドマネージャー
    SoundManager* m_soundManager;

    // ★追記ココまで↑↑↑★

    // フルスクリーン関連
private:
    // ★追記
    BOOL m_fullScreen;

public:
    // 追記
    // 画面モードを変更する関数（TRUE:フルスクリーン）
    void SetFullscreenState(BOOL value)
    {
        m_fullScreen = value;
        m_deviceResources->GetSwapChain()->SetFullscreenState(value, nullptr);
        if (value) m_deviceResources->CreateWindowSizeDependentResources();
    }

};
