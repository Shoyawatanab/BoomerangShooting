#pragma once


//状態・・状態遷移などに使用
//活動・・どんなことがをしたか　起こったか

//ゲームの種類
enum class SceneMessageType : int
{
	NONE = -1

	//ゲームの活動
	,GAME_CLEAR                                    //ゲームクリア
	,GAME_OVER									   //ゲームオーバー
	,ENEMY_DAMAGE                                  //敵のダメージ
	,EXPLOSITION_EFFECT                            //爆発エフェクト
	,CREATE_CHARGE_EFFECT                          //チャージエフェクトの作成
	,CREATE_PARTICLE_EFFECT                        //パーティクルの作成

	//ゲームの状態



	//プレイヤの活動
	,PLAYER_GET_REDAY                              //プレイヤの構えの活動
	,PLAYER_GET_REDAY_END                          //プレイヤの構え終了の活動
	,PLAYER_DAMAGE                                 //プレイヤのダメージ

	//プレイヤの状態
	,PLAYER_IDLE_STATE                             //プレイヤの通常状態
	,PLAYER_BOOMERANG_ATTACK_STATE                 //プレイヤのブーメラン攻撃状態
	,PLAYER_BOOMERANG_GET_READY_STATE              //プレイヤのブーメランの構え状態

	//ブーメランの活動
	, BOOMERANG_GET_READY                          //ブーメランを構える活動
	, BOOMERANG_THROW                              //ブーメランを投げる活動
	, BOOMERANG_THROW_STOP                         //ブーメランを投げるのをやめる活動
	, BOOMERANG_CATCH                             //ブーメランをキャッチする活動


	//ブーメランの状態
	,BOOMERANG_IDEL_STATE                         //ブーメランの通常状態
	,BOOMERANG_GET_READY_STATE                    //ブーメランの構え状態
	,BOOMERANG_THROW_STATE                        //ブーメランの投げ状態

	//ボス敵の活動
	,BOSS_DAMAGE                                 //ボスがダメージを受けた活動
	,BOSS_DEFEATED                               //ボスを倒した活動
	,BOSS_BEAM_IMPACT                            //ボスビームの着弾

	//ボステキの状態
	,BOSS_IDLE_STATE                              //ボス敵の通常状態
	,BOSS_BEAM_ATTACK_STATE                       //ボス敵のビーム攻撃状態
	,BOSS_JUMP_ATTACK_STATE                       //ボス敵のジャンプ攻撃状態
	,BOSS_WAKING_STATE	                          //ボス敵の歩き状態
	,BOSS_SWING_DOWN_STATE	                      //ボス敵の振り下ろし攻撃状態

};

//敵のダメージ時の構造体
struct EnemyDamageDatas
{
	float Damage;
	DirectX::SimpleMath::Vector3 Position;
};

//爆発エフェクト時の追加データ用構造体
struct  ExplosionEffectDatas
{
	DirectX::SimpleMath::Vector3 Scale;      //大きさ
	DirectX::SimpleMath::Vector3 Position;	 //座標
};

//チャージエフェクトの追加データ構造体
struct CreateChargeEffectDatas
{
	DirectX::SimpleMath::Vector3 Scale;      //大きさ
	DirectX::SimpleMath::Vector3 Position;	 //座標

};

/*
	名前　　　　　　　　　　　　　　　　　　追加データ (型名・用途,型名・用途　・・・・)
	BOOMERANG_IDEL_STATE 　　　　　　　　　Boomerang  どのブーメランのステートを切り替えるのか

	ENEMY_DAMAGE　　　　　　　　　　　　　 EnemyDamageDatas　構造体

	BOSS_DAMAGE　　　　　　　　　　　　　　float  残りHP割合　
	
	EXPLOSITION_EFFECT　　　　　　　　　　 ExplosionEffectDatas　構造体

	CREATE＿CHARGE_EFFECT                  CrateChargeEffectDtas 構造体
	　
*/













