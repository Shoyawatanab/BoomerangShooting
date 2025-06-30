#pragma once

class Params
{
public:


	static const float MOUSE_RADIUS;
	 
	//重力
	static const float GRAVITY;
	//影のY座標
	static const float SHADOW_POSITION_Y;
	//地上摩擦力
	static const float GRAUND_FRICTION;

//プレイヤ
   	//プレイヤの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_SCALE;
	//プレイヤの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_POSITION;
	//プレイヤの回転
	static const DirectX::SimpleMath::Quaternion PLAYER_ROTATION;
	//プレイヤのボックスの当たり判定の大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_BOX_COLLIDER_SIZE;
	//プレイヤのスフィアの当たり判定の大きさ
	static const float PLAYER_SPHERE_COLLIDER_SIZE;
	//プレイヤのHP
	static const int PLAYER_HP;
	//プレイヤの動くスピード
	static const float PLAYER_MOVE_SPEED;
	//プレイヤの回転スピード
	static const float PLAYER_ROTATION_SPEED;

	//プレイヤの影の大きさ
	static const float PLAYER_SHADOW_RADIUS;

	//プレイヤのBODYの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_BODY_SCALE;
	//プレイヤのBODYの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_BODY_POSITION;
	//プレイヤのBODYの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_BODY_ROTATION;

	//プレイヤのHEADの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_HEAD_SCALE;
	//プレイヤのHEADの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_HEAD_POSITION;
	//プレイヤのHEADの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_HEAD_ROTATION;

	//プレイヤのLEFRARMの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRARM_SCALE;
	//プレイヤのLEFRARMの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRARM_POSITION;
	//プレイヤのLEFRARMの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_LEFRARM_ROTATION;

	//プレイヤのLEFRFEETの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRFEET_SCALE;
	//プレイヤのLEFRFEETの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRFEET_POSITION;
	//プレイヤのLEFRFEETの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_LEFRFEET_ROTATION;


	//プレイヤのRIGHTARMの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTARM_SCALE;
	//プレイヤのRIGHTARMの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTARM_POSITION;
	//プレイヤのRIGHTARMの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_RIGHTARM_ROTATION;

	//プレイヤのRIGHTFEETの大きさ
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTFEET_SCALE;
	//プレイヤのRIGHTFEETの座標
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTFEET_POSITION;
	//プレイヤのRIGHTFEETの座標
	static const DirectX::SimpleMath::Quaternion PLAYER_RIGHTFEET_ROTATION;




//ブーメラン
	//ブーメランの大きさ
	static const DirectX::SimpleMath::Vector3 BOOMERANG_SCALE;
	//ブーメランの座標
	static const DirectX::SimpleMath::Vector3 BOOMERANG_POSITION;
	//ブーメランの回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_ROTATION;
	//ブーメランの数
	static int BOOMERANG_MAX_COUNT;
	//ブーメランの移動スピード
	static const float BOOMERANG_MOVE_SPEED;
	//ブーメランの横回転スピード
	static const float BOOMERANG_HORIZONTAL_ROTATION_SPEED;
	//ブーメランの投げてる時の初めの回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_START_ROTATION;
	//ブーメランの投げてる時の中間の回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_MIDDLE_ROTATION;
	//ブーメランの投げてる時の終わりの回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_END_ROTATION;

	//ブーメランのボックスの当たり判定の大きさ
	static const DirectX::SimpleMath::Vector3 BOOMERANG_BOX_COLLIDER_SIZE;
	//ブーメランのスフィアの当たり判定の大きさ
	static const float BOOMERANG_SPHERE_COLLIDER_SIZE;
	//　ブーメランの攻撃力
	static const int BOOMERANG_DAMAGE;


	//ブーメランの影の大きさ
	static const float BOOMERANG_SHADOW_RADIUS;


	//ブーメランのIDLE状態の座標
	static const DirectX::SimpleMath::Vector3 BOOMERANG_IDLE_POSITION;
	//ブーメランのIDLE状態の回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_IDLE_ROTATION;
	//ブーメランのIDLE状態の大きさ
	static const DirectX::SimpleMath::Vector3 BOOMERANG_IDLE_SCALE;

	//ブーメランのGETREADY状態の座標
	static const DirectX::SimpleMath::Vector3 BOOMERANG_GETREADY_POSITION;
	//ブーメランのGETREADY状態の回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_GETREADY_ROTATION;


	//ブーメランのTHROW状態の座標
	static const DirectX::SimpleMath::Vector3 BOOMERANG_THROW_POSITION;
	//ブーメランのTHROW状態の回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_ROTATION;
	//ブーメランの基準点の回転
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_POINT_ROTATE;


	//敵の回転の許容範囲
	static const float ENEMY_PERMISSIBLE_ANGLE;

//ボス敵
	//ボス敵のHP
	static const int BOSSENEMY_MAX_HP;
	//ボス敵の動くスピード
	static const float BOSSENEMY_MOVE_SPEED;
	//ボス敵の回転スピード
	static const float BOSSENEMY_ROTATION_SPEED;


	//ボスの影の大きさ
	static const float BOSSENEMY_SHADOW_RADIUS;


	//ボス敵のボックスの当たり判定の大きさ
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BOX_COLLIDER_SIZE;
	//ボス敵のスフィアの当たり判定の大きさ
	static const float BOSSENEMY_SPHERE_COLLIDER_SIZE;

	//ボス敵のビームの発射位置
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_SHOT_POSITION;

	//ボスビームの大きさ
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_SCALE;
	//ボスビームの座標
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_POSITION;
	//ボスビームの回転
	static const DirectX::SimpleMath::Quaternion BOSSENEMY_BEAM_ROTATION;
	//ボスビームのエネルギー弾のボックスの当たり判定の大きさ
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_BALL_BOX_COLLIDER_SIZE;
	//ボスビームのエネルギー弾のスフィアの当たり判定の大きさ
	static const float BOSSENEMY_BEAM_BALL_SPHERE_COLLIDER_SIZE;


	//ボスビームの縮小時間
	static const float BOSSENEMY_BEAM_SHRINK_TIME;
	//ボスビームのエネルギー弾の最大の大きさ
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_BALL_MAX_SCALE;
	//ボスビームのエネルギー弾の予備動作の時間
	static const float BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME;
	//ボスビームのエネルギー弾の溜めの時間
	static const float BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;
	//ボスビームのエネルギー弾の動くスピード
	static const float BOSSENEMY_BEAM_BALL_MOVE_SPPED;
	//ボスビームの光線の最大の大きさ
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_RAYS_MAX_SCALE;
	//ボスビームのチャージエフェクトの生成間隔
	static const float BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME;
	//ボスビームのチャージエフェクトの動くスピード
	static const float BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;


	//ボス敵のBODYの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_SCALE;
	//ボス敵のBODYの座標
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_POSITION;
	//ボス敵のBODYの回転
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_BODY_ROTATION;
	//ボス敵のBODYのボックスの当たり判定の大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_BOX_COLLIDER_SIZE;
	//ボス敵のBODYのスフィアの当たり判定の大きさ
	static const  float BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE;
	//ボス敵のBODYのHP
	static const  int BOSSENEMY_BODY_HP;

	//ボス敵のHEADの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_SCALE;
	//ボス敵のHEADの座標								  
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_POSITION;
	//ボス敵のHEADの回転								  
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_HEAD_ROTATION;
	//ボス敵のHEADのボックスの当たり判定の大きさ		  
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_BOX_COLLIDER_SIZE;
	//ボス敵のHEADのスフィアの当たり判定の大きさ		  
	static const  float BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE;
	//ボス敵のHEADのHP									
	static const  int BOSSENEMY_HEAD_HP;


	//ボス敵のLEFTARMの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_SCALE;
	//ボス敵のLEFTARMの座標								 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_POSITION;
	//ボス敵のLEFTARMの回転								 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTARM_ROTATION;
	//ボス敵のLEFTARMのボックスの当たり判定の大きさ		 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE;
	//ボス敵のLEFTARMのスフィアの当たり判定の大きさ		 
	static const  float BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE;
	//ボス敵のLEFTARMのHP								 
	static const int BOSSENEMY_LEFTARM_HP;

	//ボス敵のLEFTARMJOINTの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_SCALE;
	//ボス敵のLEFTARMJOINTの座標						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_POSITION;
	//ボス敵のLEFTARMJOINTの回転						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTARMJOINT_ROTATION;
	//ボス敵のLEFTARMJOINTのボックスの当たり判定の大きさ 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE;
	//ボス敵のLEFTARMJOINTのスフィアの当たり判定の大きさ 
	static const  float BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE;
	//ボス敵のLEFTARMJOINTのHP							 
	static const  int BOSSENEMY_LEFTARMJOINT_HP;

	//ボス敵のLEFTLEGの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_SCALE;
	//ボス敵のLEFTLEGの座標						 		
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_POSITION;
	//ボス敵のLEFTLEGの回転						 		 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTLEG_ROTATION;
	//ボス敵のLEFTLEGのボックスの当たり判定の大きさ 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE;
	//ボス敵のLEFTLEGのスフィアの当たり判定の大きさ 	 
	static const float BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE;
	//ボス敵のLEFTLEGのHP							 	 
	static const  int BOSSENEMY_LEFTLEG_HP;

	//ボス敵のLEFTSHOULDERの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_SCALE;
	//ボス敵のLEFTSHOULDERの座標						
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_POSITION;
	//ボス敵のLEFTSHOULDERの回転						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTSHOULDER_ROTATION;
	//ボス敵のLEFTSHOULDERのボックスの当たり判定の大きさ 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE;
	//ボス敵のLEFTSHOULDERのスフィアの当たり判定の大きさ 
	static const  float BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE;
	//ボス敵のLEFTSHOULDERのHP							 
	static const  int BOSSENEMY_LEFTSHOULDER_HP;


	//ボス敵のLEFTTHIGHの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_SCALE;
	//ボス敵のLEFTTHIGHの座標							 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_POSITION;
	//ボス敵のLEFTTHIGHの回転						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTTHIGH_ROTATION;
	//ボス敵のLEFTTHIGHのボックスの当たり判定の大きさ 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE;
	//ボス敵のLEFTTHIGHのスフィアの当たり判定の大きさ 	 
	static const  float BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE;
	//ボス敵のLEFTTHIGHのHP							 	 
	static const int BOSSENEMY_LEFTTHIGH_HP;


	//ボス敵のPELVISの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_SCALE;
	//ボス敵のPELVISの座標							 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_POSITION;
	//ボス敵のPELVISの回転						 	 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_PELVIS_ROTATION;
	//ボス敵のPELVISのボックスの当たり判定の大きさ 	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE;
	//ボス敵のPELVISのスフィアの当たり判定の大きさ 	 	 
	static const  float BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE;
	//ボス敵のPELVISのHP							 	 
	static const  int BOSSENEMY_PELVIS_HP;


	//ボス敵のRIGHTARMの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_SCALE;
	//ボス敵のRIGHTARMの座標							 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_POSITION;
	//ボス敵のRIGHTARMの回転						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTARM_ROTATION;
	//ボス敵のRIGHTARMのボックスの当たり判定の大きさ 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE;
	//ボス敵のRIGHTARMのスフィアの当たり判定の大きさ 	 
	static const  float BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE;
	//ボス敵のRIGHTARMのHP							 	 
	static const  int BOSSENEMY_RIGHTARM_HP;

	//ボス敵のRIGHTARMJOINTの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_SCALE;
	//ボス敵のRIGHTARMJOINTの座標						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_POSITION;
	//ボス敵のRIGHTARMJOINTの回転						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTARMJOINT_ROTATION;
	//ボス敵のRIGHTARMJOINTのボックスの当たり判定の大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE;
	//ボス敵のRIGHTARMJOINTのスフィアの当たり判定の大きさ
	static const  float BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE;
	//ボス敵のRIGHTARMJOINTのHP							 
	static const  int BOSSENEMY_RIGHTARMJOINT_HP;


	//ボス敵のRIGHTLEGの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_SCALE;
	//ボス敵のRIGHTLEGの座標						 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_POSITION;
	//ボス敵のRIGHTLEGの回転						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTLEG_ROTATION;
	//ボス敵のRIGHTLEGのボックスの当たり判定の大きさ	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_BOX_COLLIDER_SIZE;
	//ボス敵のRIGHTLEGのスフィアの当たり判定の大きさ	 
	static const float BOSSENEMY_RIGHTLEG_SPHERE_COLLIDER_SIZE;
	//ボス敵のRIGHTLEGのHP							 	 
	static const  int BOSSENEMY_RIGHTLEG_HP;

	//ボス敵のRIGHTSHOULDERの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_SCALE;
	//ボス敵のRIGHTSHOULDERの座標						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_POSITION;
	//ボス敵のRIGHTSHOULDERの回転						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTSHOULDER_ROTATION;
	//ボス敵のRIGHTSHOULDERのボックスの当たり判定の大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE;
	//ボス敵のRIGHTSHOULDERのスフィアの当たり判定の大きさ
	static const  float BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE;
	//ボス敵のRIGHTSHOULDERのHP							 
	static const  int BOSSENEMY_RIGHTSHOULDER_HP;


	//ボス敵のRIGHTTHIGHの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_SCALE;
	//ボス敵のRIGHTTHIGHの座標						 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_POSITION;
	//ボス敵のRIGHTTHIGHの回転						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTTHIGH_ROTATION;
	//ボス敵のRIGHTTHIGHのボックスの当たり判定の大きさ	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE;
	//ボス敵のRIGHTTHIGHのスフィアの当たり判定の大きさ	 
	static const  float BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE;
	//ボス敵のRIGHTTHIGHのHP							 
	static const  int BOSSENEMY_RIGHTTHIGH_HP;


	//ボス敵のTORSOの大きさ
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_SCALE;
	//ボス敵のTORSOの座標						 	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_POSITION;
	//ボス敵のTORSOの回転						 	 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_TORSO_ROTATION;
	//ボス敵のTORSOのボックスの当たり判定の大きさ	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_BOX_COLLIDER_SIZE;
	//ボス敵のTORSOのスフィアの当たり判定の大きさ	 	 
	static const  float BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE;
	//ボス敵のTORSOのHP							 		 
	static const  int BOSSENEMY_TORSO_HP;


//鳥の敵
	//鳥の敵のHP
	static const int BIRDENEMY_HP;
	//鳥の敵のボックスの当たり判定の大きさ
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BOX_COLLIDER_SIZE;
	//鳥の敵のスフィアの当たり判定の大きさ
	static const float BIRDENEMY_SPHERE_COLLIDER_SIZE;
	//鳥の敵の影の大きさ
	static const float BIRDENEMY_SHADOW_RADIUS;

	//鳥の敵のビームの発射座標
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BEAM_SHOT_POSITION;
	//鳥の敵の動くのにかかる時間
	static const float BIRDENEMY_MOVE_TIME;
	//鳥の敵の行動の最小間隔
	static const float BIRDENEMY_ACTIONS_MIN_TIME;
	//鳥の敵の行動の最大間隔
	static const float BIRDENEMY_ACTIONS_MAX_TIME;
	//鳥の敵の行動半径
	static const float BIRDENEMY_MOVE_RADIUS;
	//鳥の敵の攻撃の確率
	static const float BIRDENEMY_ATTACK_RATIO;
	
	//鳥の敵のBODYの大きさ
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BODY_SCALE;
	//鳥の敵のBODYの座標
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BODY_POSITION;
	//鳥の敵のBODYの回転
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_BODY_ROTATION;

	//鳥の敵のLEFTFEATHERの大きさ
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_LEFTFEATHER_SCALE;
	//鳥の敵のLEFTFEATHERの座標						
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_LEFTFEATHER_POSITION;
	//鳥の敵のLEFTFEATHERの回転						
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_LEFTFEATHER_ROTATION;


	//鳥の敵のRIGHTFEATHERの大きさ
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_RIGHTFEATHER_SCALE;
	//鳥の敵のRIGHTFEATHERの座標						
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_RIGHTFEATHER_POSITION;
	//鳥の敵のRIGHTFEATHERの回転						
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_RIGHTFEATHER_ROTATION;


	//鳥の敵のエネルギー弾の最大の大きさ
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BEAM_BALL_MAX_SIZE;
	//鳥の敵のエネルギー弾の溜め時間
	static const float BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME;

	//鳥の敵のエネルギー弾の初速度
	static const float BIRDENEMY_BEAM_BALL_INITIAL_SPEED;
	//鳥の敵のエネルギー弾の最終速度
	static const float BIRDENEMY_BEAM_BALL_FAINAL_SPEED;
	//鳥の敵のエネルギー弾の減速率
	static const float BIRDENEMY_BEAM_BALL_DECELERATION_TIME;

};

