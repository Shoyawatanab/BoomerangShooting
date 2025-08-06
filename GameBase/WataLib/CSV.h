/*
	クラス名     : CSV
	説明         : CSVの読み込みクラス
	補足・注意点 :
*/
#pragma once

namespace WataLib
{
	class CSV final
	{
	public:
		//ブーメランの軌道の座標の取得
		static std::vector<DirectX::SimpleMath::Vector3> LoadCSVBoomerang();

	};
}
