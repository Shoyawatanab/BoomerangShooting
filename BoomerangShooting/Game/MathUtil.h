#pragma once
#include "pch.h"
#include "GameBase/Screen.h"
#include <random>


namespace MathUtil
{
    /// <summary>
    /// Lerp関数
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    template<typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a + (b - a) * t;
    }



    /// <summary>
    /// Vector3をQuaternionに変換
    /// </summary>
    /// <param name="vector3"></param>
    /// <returns></returns>
    inline DirectX::SimpleMath::Quaternion ChangeVector3ToQuaternion(
        DirectX::SimpleMath::Vector3 vector3
    )
    {
       return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
            DirectX::XMConvertToRadians(vector3.y),
            DirectX::XMConvertToRadians(vector3.x),
            DirectX::XMConvertToRadians(vector3.z));

    }


    /// <summary>
    /// ワールド座標をスクリーン座標に変換
    /// </summary>
    /// <param name="worldPos">ワールド座標</param>
    /// <param name="worldMatrix">ワールドマトリックス</param>
    /// <param name="viewMatrix">ビュー行列</param>
    /// <param name="projectionMatrix">射影行列</param>
    /// <returns>スクリーン座標</returns>
    inline DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos
        , const DirectX::SimpleMath::Matrix& worldMatrix, const DirectX::SimpleMath::Matrix& viewMatrix
        , const DirectX::SimpleMath::Matrix& projectionMatrix)
    {
        using namespace DirectX::SimpleMath;
        // ワールド座標を変換するための行列を結合
        Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

        // ワールド座標をプロジェクション空間に変換
        Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

        // 射影された座標をスクリーン座標に変換
        float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * Screen::WIDTH;
        float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * Screen::HEIGHT;

        return Vector2(x, y);
    }

    template<typename T>
    inline T GetRandom(const T minValue,const T maxValue)
    {
        //	完全なランダムをハードウェア的に生成するためのクラスの変数
        std::random_device seed;
        //	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
        //	※「default_random_engine」はusingで「mt19937」となっている
        std::default_random_engine engine(seed());
        //	生成して欲しいランダムの範囲をDistributionに任せる。今回は0～2PI
        std::uniform_real_distribution<> dist(minValue,maxValue);

        return dist(engine);

    }


}
