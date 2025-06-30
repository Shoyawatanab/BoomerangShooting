#include "pch.h"
#include "Params.h"

using namespace DirectX::SimpleMath;

const float            Params::MOUSE_RADIUS = 1.0f;


//重力
const float            Params::GRAVITY = -9.5;

const float            Params::SHADOW_POSITION_Y = 0.1f;

//地上摩擦力
const float            Params::GRAUND_FRICTION =  0.95f;

//プレイヤの大きさ
const Vector3          Params::PLAYER_SCALE = Vector3(0.2f, 0.2f, 0.2f);
//プレイヤの座標
const Vector3          Params::PLAYER_POSITION = Vector3(0.0f,0.55f,5.0f);
//プレイヤの回転
const Quaternion       Params::PLAYER_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																			 ,DirectX::XMConvertToRadians(0)
																			 ,DirectX::XMConvertToRadians(0));

//プレイヤの影の大きさ
const float            Params::PLAYER_SHADOW_RADIUS = 0.5f;


//プレイヤのボックスの当たり判定の大きさ
const Vector3          Params::PLAYER_BOX_COLLIDER_SIZE = Vector3(2.0f,3.0f,2.0f);
//プレイヤのスフィアの当たり判定の大きさ
const float            Params::PLAYER_SPHERE_COLLIDER_SIZE = 4.0f;
//プレイヤのHP
const int              Params::PLAYER_HP = 3;
//プレイヤの動くスピード
const float            Params::PLAYER_MOVE_SPEED = 10.0f;
//プレイヤの回転スピード
const float            Params::PLAYER_ROTATION_SPEED = 10.0f;
//プレイヤのBODYの大きさ
const Vector3         Params::PLAYER_BODY_SCALE = Vector3::One;
//プレイヤのBODYの座標
const Vector3         Params::PLAYER_BODY_POSITION = Vector3(0.0f,-0.28f,0.0f);
//プレイヤのBODYの座標
const Quaternion      Params::PLAYER_BODY_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(0));
//プレイヤのHEADの大きさ
const Vector3         Params::PLAYER_HEAD_SCALE = Vector3::One;
//プレイヤのHEADの座標
const Vector3         Params::PLAYER_HEAD_POSITION = Vector3(0.0f, 2.4f, 0.0f);
//プレイヤのHEADの座標
const Quaternion      Params::PLAYER_HEAD_ROTATION = Quaternion::Identity;

//プレイヤのLEFRARMの大きさ
const Vector3         Params::PLAYER_LEFRARM_SCALE = Vector3::One;
//プレイヤのLEFRARMの座標
 const Vector3        Params::PLAYER_LEFRARM_POSITION = Vector3(1.45f,0.8f,0.0f);
//プレイヤのLEFRARMの座標
 const Quaternion     Params::PLAYER_LEFRARM_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																						 , DirectX::XMConvertToRadians(0)
																						 , DirectX::XMConvertToRadians(3));
//プレイヤのLEFRFEETの大きさ
 const Vector3       Params::PLAYER_LEFRFEET_SCALE = Vector3::One;
//プレイヤのLEFRFEETの座標
 const Vector3       Params::PLAYER_LEFRFEET_POSITION = Vector3(0.5f, -1.1f, 0.0f);
//プレイヤのLEFRFEETの座標
 const Quaternion    Params::PLAYER_LEFRFEET_ROTATION = Quaternion::Identity;
//プレイヤのRIGHTARMの大きさ
 const Vector3      Params::PLAYER_RIGHTARM_SCALE = Vector3::One;
//プレイヤのRIGHTARMの座標
 const Vector3      Params::PLAYER_RIGHTARM_POSITION = Vector3(-1.45f, 0.8f, 0.0f);
//プレイヤのRIGHTARMの座標
 const Quaternion   Params::PLAYER_RIGHTARM_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180)
																						, DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(3));
//プレイヤのRIGHTFEETの大きさ
 const Vector3      Params::PLAYER_RIGHTFEET_SCALE = Vector3::One;
//プレイヤのRIGHTFEETの座標
 const Vector3      Params::PLAYER_RIGHTFEET_POSITION = Vector3(-0.5f, -1.1f, 0.0f);
//プレイヤのRIGHTFEETの座標
 const Quaternion   Params::PLAYER_RIGHTFEET_ROTATION = Quaternion::Identity;



//ブーメランの大きさ
const Vector3          Params::BOOMERANG_SCALE = Vector3(10.0f,10.0f,10.f);
//ブーメランの座標
const Vector3          Params::BOOMERANG_POSITION = Vector3(0.0f,0.5f,0.0f);
//ブーメランの回転
const Quaternion       Params::BOOMERANG_ROTATION = Quaternion::Identity;
//ブーメランの数
int Params::BOOMERANG_MAX_COUNT = 3;
//ブーメランの移動スピード
 const float Params::BOOMERANG_MOVE_SPEED = 8.0f;
//ブーメランの横回転スピード
 const float Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED = 20.0f;
//ブーメランの投げてる時の初めの回転
 const  Quaternion Params::BOOMERANG_THROW_START_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(45.0f));
 ;
//ブーメランの投げてる時の中間の回転
 const  Quaternion Params::BOOMERANG_THROW_MIDDLE_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f));
 ;
//ブーメランの投げてる時の終わりの回転
 const  Quaternion Params::BOOMERANG_THROW_END_ROTATION =  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(-45.0f));

//ブーメランのボックスの当たり判定の大きさ
 const  Vector3 Params::BOOMERANG_BOX_COLLIDER_SIZE = Vector3(0.21f, 0.2f, 0.21f);
//ブーメランのスフィアの当たり判定の大きさ
 const float Params::BOOMERANG_SPHERE_COLLIDER_SIZE = 0.4f;
//　ブーメランの攻撃力
 const int Params::BOOMERANG_DAMAGE = 10;

 //ブーメランの影の大きさ
 const float Params::BOOMERANG_SHADOW_RADIUS = 0.5f ;

//ブーメランのIDLE状態の座標
 const  Vector3 Params::BOOMERANG_IDLE_POSITION = Vector3(0.0f,0.5f,-1.1f);
//ブーメランのIDLE状態の回転
 const  Quaternion Params::BOOMERANG_IDLE_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180.0f)
																						 , DirectX::XMConvertToRadians(90.0f)
																						 , DirectX::XMConvertToRadians(0.0f));
 //ブーメランのIDLE状態の大きさ
 const  Vector3 Params::BOOMERANG_IDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);


//ブーメランのGETREADY状態の座標
 const  Vector3 Params::BOOMERANG_GETREADY_POSITION = Vector3(-1.5f,3.5f,0.5f);
//ブーメランのGETREADY状態の回転
 const  Quaternion Params::BOOMERANG_GETREADY_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-90.0f)
																							 , DirectX::XMConvertToRadians(90.0f)
																							 , DirectX::XMConvertToRadians(0.0f));

//ブーメランのTHROW状態の座標
 const  Vector3 Params::BOOMERANG_THROW_POSITION;
//ブーメランのTHROW状態の回転
 const  Quaternion Params::BOOMERANG_THROW_ROTATION;
 //ブーメランの基準点の回転
 const Quaternion Params::BOOMERANG_THROW_POINT_ROTATE = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180.0f)
																				 , DirectX::XMConvertToRadians(0.0f)
																				 , DirectX::XMConvertToRadians(0.0f));


 //敵の回転の許容範囲
 const float Params::ENEMY_PERMISSIBLE_ANGLE = 15.0f;


 //ボス敵
	 //ボス敵のHP
 const int Params::BOSSENEMY_MAX_HP = 500;
 //ボス敵の動くスピード
 const float Params::BOSSENEMY_MOVE_SPEED = 2.0f;
 //ボス敵の回転スピード
 const float Params::BOSSENEMY_ROTATION_SPEED = 1.0f;

 //ボスの影の大きさ
 const float Params::BOSSENEMY_SHADOW_RADIUS = 3.5f;

 //パーツごとのHP
  //ボス敵のBODYのHP
 const  int Params::BOSSENEMY_BODY_HP			= 100;
 //ボス敵のHEADのHP						  			
 const  int Params::BOSSENEMY_HEAD_HP			= 100;
 //ボス敵のLEFTARMのHP						  		 
 const  int Params::BOSSENEMY_LEFTARM_HP		= 100;
 //ボス敵のLEFTARMJOINTのHP							 
 const  int Params::BOSSENEMY_LEFTARMJOINT_HP	= 100;
 //ボス敵のLEFTLEGのHP							 	 
 const  int Params::BOSSENEMY_LEFTLEG_HP		= 100;
 //ボス敵のLEFTSHOULDERのHP							 
 const  int Params::BOSSENEMY_LEFTSHOULDER_HP	= 100;
 //ボス敵のLEFTTHIGHのHP							 	 
 const  int Params::BOSSENEMY_LEFTTHIGH_HP		= 100;
 //ボス敵のPELVISのHP							 	 
 const  int Params::BOSSENEMY_PELVIS_HP			= 100;
 //ボス敵のRIGHTARMのHP							 	 
 const  int Params::BOSSENEMY_RIGHTARM_HP		= 100;
 //ボス敵のRIGHTARMJOINTのHP							 
 const  int Params::BOSSENEMY_RIGHTARMJOINT_HP	= 10;
 //ボス敵のRIGHTLEGのHP							 	 
 const  int Params::BOSSENEMY_RIGHTLEG_HP		= 100;
 //ボス敵のRIGHTSHOULDERのHP							 
 const  int Params::BOSSENEMY_RIGHTSHOULDER_HP	= 100;
 //ボス敵のRIGHTTHIGHのHP							 
 const  int Params::BOSSENEMY_RIGHTTHIGH_HP      = 100;
 //ボス敵のTORSOのHP							 		 
 const  int Params::BOSSENEMY_TORSO_HP			= 100;







 //ボス敵のボックスの当たり判定の大きさ
 const Vector3 Params::BOSSENEMY_BOX_COLLIDER_SIZE = Vector3(3.0f, 3.7f, 1.1f);
 //ボス敵のスフィアの当たり判定の大きさ
 const float Params::BOSSENEMY_SPHERE_COLLIDER_SIZE = 5.0f;

 //ボス敵のビームの発射位置
 const  Vector3 Params::BOSSENEMY_BEAM_SHOT_POSITION = Vector3(-2.0f, 0.5f, 5.0);


 //ボスビームの大きさ
 const Vector3 Params::BOSSENEMY_BEAM_SCALE = Vector3::One;
 //ボスビームの座標
 const Vector3 Params::BOSSENEMY_BEAM_POSITION = Vector3::Zero;
 //ボスビームの回転
 const Quaternion Params::BOSSENEMY_BEAM_ROTATION = Quaternion::Identity;
 //ボスビームのエネルギー弾のボックスの当たり判定の大きさ
 const Vector3  Params::BOSSENEMY_BEAM_BALL_BOX_COLLIDER_SIZE = Vector3(0.4f,0.4f,0.4f);
 //ボスビームのエネルギー弾のスフィアの当たり判定の大きさ
 const float  Params::BOSSENEMY_BEAM_BALL_SPHERE_COLLIDER_SIZE = 0.8f;



 //ボスビームの縮小時間
 const float Params::BOSSENEMY_BEAM_SHRINK_TIME = 0.8f;
 //ボスビームのエネルギー弾の最大の大きさ
 const Vector3 Params::BOSSENEMY_BEAM_BALL_MAX_SCALE = Vector3(1.5f,1.5f,1.5f);
 //ボスビームのエネルギー弾の予備動作の時間
 const float Params::BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME = 2.0f;
 //ボスビームのエネルギー弾の溜めの時間
 const float Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME = 3.0f;
 //ボスビームのエネルギー弾の動くスピード
 const float Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED = 20.f;
 //ボスビームの光線の最大の大きさ
 const Vector3 Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE = Vector3(1.5f,1.5f,0);
 //ボスビームのチャージエフェクトの生成間隔
 const float Params::BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME = 0.5f;
 //ボスビームのチャージエフェクトの動くスピード
 const float Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME = 1.0f;


 //ボス敵のBODYの大きさ
  const  Vector3 Params::BOSSENEMY_BODY_SCALE = Vector3::One;
 //ボス敵のBODYの座標
  const  Vector3 Params::BOSSENEMY_BODY_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //ボス敵のBODYの回転
  const  Quaternion Params::BOSSENEMY_BODY_ROTATION = Quaternion::Identity;
 //ボス敵のBODYのボックスの当たり判定の大きさ
  const  Vector3 Params::BOSSENEMY_BODY_BOX_COLLIDER_SIZE = Vector3(0.57f,0.17f,0.37f);
 //ボス敵のBODYのスフィアの当たり判定の大きさ
  const  float Params::BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE = 1.0f;

 //ボス敵のHEADの大きさ
  const  Vector3 Params::BOSSENEMY_HEAD_SCALE = Vector3::One;
 //ボス敵のHEADの座標								  
  const  Vector3 Params::BOSSENEMY_HEAD_POSITION = Vector3(0.0f,2.1f,0.0f);
 //ボス敵のHEADの回転								  
  const  Quaternion Params::BOSSENEMY_HEAD_ROTATION = Quaternion::Identity;
 //ボス敵のHEADのボックスの当たり判定の大きさ		  
  const  Vector3 Params::BOSSENEMY_HEAD_BOX_COLLIDER_SIZE = Vector3(0.13f,0.13f,0.13f);
 //ボス敵のHEADのスフィアの当たり判定の大きさ		  
  const  float Params::BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE = 0.3f;


 //ボス敵のLEFTARMの大きさ
  const  Vector3 Params::BOSSENEMY_LEFTARM_SCALE = Vector3::One;
 //ボス敵のLEFTARMの座標								 
  const  Vector3 Params::BOSSENEMY_LEFTARM_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //ボス敵のLEFTARMの回転								 
  const  Quaternion Params::BOSSENEMY_LEFTARM_ROTATION = Quaternion::Identity;
 //ボス敵のLEFTARMのボックスの当たり判定の大きさ		 
  const  Vector3 Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE = Vector3(0.08f,0.11f,0.08f);
 //ボス敵のLEFTARMのスフィアの当たり判定の大きさ		 
  const  float Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE = 0.2f;

 //ボス敵のLEFTARMJOINTの大きさ
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_SCALE = Vector3::One;
 //ボス敵のLEFTARMJOINTの座標						 
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_POSITION = Vector3(0.0f,-1.7f,0.0f);
 //ボス敵のLEFTARMJOINTの回転						 
  const  Quaternion Params::BOSSENEMY_LEFTARMJOINT_ROTATION = Quaternion::Identity;
 //ボス敵のLEFTARMJOINTのボックスの当たり判定の大きさ 
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE = Vector3(0.06f,0.1f,0.06f);
 //ボス敵のLEFTARMJOINTのスフィアの当たり判定の大きさ 
  const  float Params::BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE = 0.15f ;

 //ボス敵のLEFTLEGの大きさ
  const  Vector3 Params::BOSSENEMY_LEFTLEG_SCALE = Vector3::One;
 //ボス敵のLEFTLEGの座標						 		
  const  Vector3 Params::BOSSENEMY_LEFTLEG_POSITION = Vector3(0.0f,-0.6f,0.0f);
 //ボス敵のLEFTLEGの回転						 		 
  const  Quaternion Params::BOSSENEMY_LEFTLEG_ROTATION = Quaternion::Identity;
 //ボス敵のLEFTLEGのボックスの当たり判定の大きさ 	 
  const  Vector3 Params::BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE = Vector3(0.09f,0.09f,0.09f);
 //ボス敵のLEFTLEGのスフィアの当たり判定の大きさ 	 
  const  float Params::BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE = 0.2f;

 //ボス敵のLEFTSHOULDERの大きさ
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_SCALE = Vector3::One;
 //ボス敵のLEFTSHOULDERの座標						
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_POSITION = Vector3(2.4f,1.0f,0.0f);
 //ボス敵のLEFTSHOULDERの回転						 
  const  Quaternion Params::BOSSENEMY_LEFTSHOULDER_ROTATION = Quaternion::Identity;
 //ボス敵のLEFTSHOULDERのボックスの当たり判定の大きさ 
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE = Vector3(0.12f,0.2f,0.12f);
 //ボス敵のLEFTSHOULDERのスフィアの当たり判定の大きさ 
  const  float Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE = 0.5f;



 //ボス敵のLEFTTHIGHの大きさ
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_SCALE = Vector3::One;
 //ボス敵のLEFTTHIGHの座標							 
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_POSITION = Vector3(0.9f,-0.7f,0.0f);
 //ボス敵のLEFTTHIGHの回転						 	 
  const  Quaternion Params::BOSSENEMY_LEFTTHIGH_ROTATION = Quaternion::Identity;
 //ボス敵のLEFTTHIGHのボックスの当たり判定の大きさ 	 
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE= Vector3(0.1f,0.13f,0.1f);
 //ボス敵のLEFTTHIGHのスフィアの当たり判定の大きさ 	 
  const  float Params::BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE = 0.2f;


 //ボス敵のPELVISの大きさ
  const  Vector3 Params::BOSSENEMY_PELVIS_SCALE = Vector3::One;
 //ボス敵のPELVISの座標							 	 
  const  Vector3 Params::BOSSENEMY_PELVIS_POSITION = Vector3(0.0f,0.7f,0.0f);
 //ボス敵のPELVISの回転						 	 	 
  const  Quaternion Params::BOSSENEMY_PELVIS_ROTATION = Quaternion::Identity;
 //ボス敵のPELVISのボックスの当たり判定の大きさ 	 	 
  const  Vector3 Params::BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE = Vector3(0.3f,0.1f,0.25f);
 //ボス敵のPELVISのスフィアの当たり判定の大きさ 	 	 
  const  float Params::BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE = 0.5f;


 //ボス敵のRIGHTARMの大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTARM_SCALE = Vector3::One;
 //ボス敵のRIGHTARMの座標							 
  const  Vector3 Params::BOSSENEMY_RIGHTARM_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //ボス敵のRIGHTARMの回転						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTARM_ROTATION = Quaternion::Identity;
 //ボス敵のRIGHTARMのボックスの当たり判定の大きさ 	 
  const  Vector3 Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE = Vector3(0.08f,0.11f,0.08f);
 //ボス敵のRIGHTARMのスフィアの当たり判定の大きさ 	 
  const  float Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE = 0.2f;

 //ボス敵のRIGHTARMJOINTの大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_SCALE = Vector3::One;
 //ボス敵のRIGHTARMJOINTの座標						 
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_POSITION = Vector3(0.0f,-1.7f,0.0f);
 //ボス敵のRIGHTARMJOINTの回転						 
  const  Quaternion Params::BOSSENEMY_RIGHTARMJOINT_ROTATION = Quaternion::Identity;
 //ボス敵のRIGHTARMJOINTのボックスの当たり判定の大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE = Vector3(0.06f,0.1f,0.06f);
 //ボス敵のRIGHTARMJOINTのスフィアの当たり判定の大きさ
  const  float Params::BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE = 0.15f;


 //ボス敵のRIGHTLEGの大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_SCALE = Vector3::One;
 //ボス敵のRIGHTLEGの座標						 	 
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_POSITION = Vector3(0.0f,-0.6f,0.0f);
 //ボス敵のRIGHTLEGの回転						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTLEG_ROTATION = Quaternion::Identity;
 //ボス敵のRIGHTLEGのボックスの当たり判定の大きさ	 
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_BOX_COLLIDER_SIZE = Vector3(0.09f,0.09f,0.09f);
 //ボス敵のRIGHTLEGのスフィアの当たり判定の大きさ	 
  const  float Params::BOSSENEMY_RIGHTLEG_SPHERE_COLLIDER_SIZE = 0.2f;

 //ボス敵のRIGHTSHOULDERの大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_SCALE = Vector3::One;
 //ボス敵のRIGHTSHOULDERの座標						 
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_POSITION = Vector3(-2.4f,1.0f,0.0f);
 //ボス敵のRIGHTSHOULDERの回転						 
  const  Quaternion Params::BOSSENEMY_RIGHTSHOULDER_ROTATION = Quaternion::Identity;
 //ボス敵のRIGHTSHOULDERのボックスの当たり判定の大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE = Vector3(0.12f,0.2f,0.12f);
 //ボス敵のRIGHTSHOULDERのスフィアの当たり判定の大きさ
  const  float Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE = 0.5f;


 //ボス敵のRIGHTTHIGHの大きさ
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_SCALE = Vector3::One;
 //ボス敵のRIGHTTHIGHの座標						 	 
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_POSITION = Vector3(-0.9f,-0.7f,0.0f);
 //ボス敵のRIGHTTHIGHの回転						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTTHIGH_ROTATION = Quaternion::Identity;
 //ボス敵のRIGHTTHIGHのボックスの当たり判定の大きさ	 
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE = Vector3(0.1f,0.13f,0.1f);
 //ボス敵のRIGHTTHIGHのスフィアの当たり判定の大きさ	 
  const  float Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE = 0.2f;

 //ボス敵のTORSOの大きさ
  const  Vector3 Params::BOSSENEMY_TORSO_SCALE = Vector3::One;
 //ボス敵のTORSOの座標						 	 	 
  const  Vector3 Params::BOSSENEMY_TORSO_POSITION = Vector3(0.0f,1.7f,0.0f);
 //ボス敵のTORSOの回転						 	 	 
  const  Quaternion Params::BOSSENEMY_TORSO_ROTATION = Quaternion::Identity;
 //ボス敵のTORSOのボックスの当たり判定の大きさ	 	 
  const  Vector3 Params::BOSSENEMY_TORSO_BOX_COLLIDER_SIZE = Vector3(0.4f,0.35f,0.2f);
 //ボス敵のTORSOのスフィアの当たり判定の大きさ	 	 
  const  float Params::BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE = 0.6f;


  //鳥の敵
	//鳥の敵のHP
  const int Params::BIRDENEMY_HP = 40;
  //鳥の敵のボックスの当たり判定の大きさ
  const  Vector3 Params::BIRDENEMY_BOX_COLLIDER_SIZE = Vector3(0.7f,0.3f,0.7f);
  //鳥の敵のスフィアの当たり判定の大きさ
  const float Params::BIRDENEMY_SPHERE_COLLIDER_SIZE = 1.0f;
  //鳥の敵の影の大きさ
  const float Params::BIRDENEMY_SHADOW_RADIUS = 0.5f;

  //鳥の敵のビームの発射座標
  const  Vector3 Params::BIRDENEMY_BEAM_SHOT_POSITION = Vector3(0.0f,0.0f,1.8f);

  //鳥の敵の動くのにかかる時間
  const float Params::BIRDENEMY_MOVE_TIME = 0.1f;
  //鳥の敵の行動の最小間隔
  const float Params::BIRDENEMY_ACTIONS_MIN_TIME = 1.0f;
  //鳥の敵の行動の最大間隔
  const float Params::BIRDENEMY_ACTIONS_MAX_TIME = 5.0f;
  //鳥の敵の行動半径
  const float Params::BIRDENEMY_MOVE_RADIUS = 2.0f;
  //鳥の敵の攻撃の確率
  const float Params::BIRDENEMY_ATTACK_RATIO = 20.0f;



  //鳥の敵のBODYの大きさ
  const  Vector3 Params::BIRDENEMY_BODY_SCALE = Vector3::One;
  //鳥の敵のBODYの座標
  const  Vector3 Params::BIRDENEMY_BODY_POSITION = Vector3::Zero;
  //鳥の敵のBODYの回転
  const  Quaternion Params::BIRDENEMY_BODY_ROTATION = Quaternion::Identity;

  //鳥の敵のLEFTFEATHERの大きさ
  const  Vector3 Params::BIRDENEMY_LEFTFEATHER_SCALE = Vector3::One;
  //鳥の敵のLEFTFEATHERの座標						
  const  Vector3 Params::BIRDENEMY_LEFTFEATHER_POSITION = Vector3(-0.5f,0.0f,0.0f);
  //鳥の敵のLEFTFEATHERの回転						
  const  Quaternion Params::BIRDENEMY_LEFTFEATHER_ROTATION = Quaternion::Identity;


  //鳥の敵のRIGHTFEATHERの大きさ
    const  Vector3 Params::BIRDENEMY_RIGHTFEATHER_SCALE = Vector3::One;
  //鳥の敵のRIGHTFEATHERの座標						
    const  Vector3 Params::BIRDENEMY_RIGHTFEATHER_POSITION = Vector3(0.5f,0.0f,0.0f);
  //鳥の敵のRIGHTFEATHERの回転						
    const  Quaternion Params::BIRDENEMY_RIGHTFEATHER_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), 
																									DirectX::XMConvertToRadians(0), 
																									DirectX::XMConvertToRadians(180));


	//鳥の敵のエネルギー弾の最大の大きさ
	const Vector3 Params::BIRDENEMY_BEAM_BALL_MAX_SIZE = Vector3(0.5f,0.5f,0.5f); 

	//鳥の敵のエネルギー弾の溜め時間
	const float Params::BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME = 2.0f;

	///鳥の敵のビーム弾の初速度
	const float Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED = 4.0f;
	///鳥の敵のビーム弾の最終速度
	const float Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED = 1.5f;
	//鳥の敵のエネルギー弾の減速率
	const float Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME = 0.3f;



