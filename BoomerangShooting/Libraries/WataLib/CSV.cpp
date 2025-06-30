/*
	@file	CSV.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "CSV.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include <fstream>
#include <string>
#include <sstream>


/// <summary>
/// ブーメランのcsvファイルの読み込み
/// </summary>
/// <returns></returns>
std::vector<DirectX::SimpleMath::Vector3> WataLib::CSV::LoadCSVBoomerang()
{
	std::string line;  //1行
	//ファイルのオープン
	std::ifstream fin(L"Resources/Dates/Boomerang.csv");
	//オーオウンできたか
	if (!fin.is_open())
	{
		//エラーなら
		return {};
	}

	std::vector<DirectX::SimpleMath::Vector3> Pos;

	//一番上を飛ばす
	std::getline(fin, line);

	for (int i = 0; std::getline(fin, line); i++)
	{

		std::istringstream stream(line);
		std::string str;

		Pos.push_back(DirectX::SimpleMath::Vector3());

		std::getline(stream, str, ',');
		Pos.back().x =  std::stof(str);
		std::getline(stream, str, ',');
		Pos.back().y= std::stof(str);
		std::getline(stream, str, ',');
		Pos.back().z = std::stof(str);

		
	}


	fin.close();

	return Pos;
}








