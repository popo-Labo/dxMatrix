#include <stdio.h>
#include <d3dx10.h>
#pragma comment( lib, "d3dx10.lib" )
#include <math.h>

int main() {
	D3DXVECTOR3 Pos		= { 2.0f, 2.0f, 0.0f };
	D3DXVECTOR3 Rot		= { D3DXToRadian( 4.0f ), D3DXToRadian( 8.0f ), D3DXToRadian( 67.0f ) };
	D3DXVECTOR3 Scale	= { 1.0f, 1.0f, 1.0f };
	D3DXVECTOR3 AddPos	= { 3.0f, 3.0f, 0.0f };
	D3DXVECTOR3 AddRot	= { D3DXToRadian( 0.0f ), D3DXToRadian( 0.0f ), D3DXToRadian( 90.0f ) };

	printf( "- 座標/回転 -\n" );
	printf( "Pos    : x = %f, y = %f, z = %f\n", Pos.x, Pos.y, Pos.z );
	printf( "Ros    : x = %f, y = %f, z = %f\n", D3DXToDegree( Rot.x ), D3DXToDegree( Rot.y ), D3DXToDegree( Rot.z ) );
	printf( "- 追加する座標/回転 -\n" );
	printf( "AddPos : x = %f, y = %f, z = %f\n", AddPos.x, AddPos.y, AddPos.z );
	printf( "AddRot : x = %f, y = %f, z = %f\n", D3DXToDegree( AddRot.x ), D3DXToDegree( AddRot.y ), D3DXToDegree( AddRot.z ) );


	D3DXMATRIX mAddWorld, mScale, mRot, mTran;
	D3DXMatrixScaling( &mScale, Scale.x, Scale.y, Scale.z );
	D3DXMatrixRotationYawPitchRoll( &mRot, Rot.y, Rot.x, Rot.z );
	D3DXMatrixTranslation( &mTran, Pos.x, Pos.y, Pos.z );
	mAddWorld = mScale * mRot * mTran;

	printf( "\n- ワールド行列を計算後、ワールド行列から座標を取得 -\n" );
	printf( "mWorld : x = %f, y = %f, z = %f\n", mAddWorld._41, mAddWorld._42, mAddWorld._43 );

	printf( "- ワールド行列を計算後、ワールド行列から回転を取得 -\n" );
	float Addx = atanf( mAddWorld._23 / mAddWorld._33 );
	float Addy = atanf( -( mAddWorld._13 * cosf( Addx ) ) / mAddWorld._33 );
	float Addz = atanf( mAddWorld._12 / mAddWorld._11 );
	printf( "Rot  : x = %f, y = %f, z = %f\n", D3DXToDegree( Addx ), D3DXToDegree( Addy ), D3DXToDegree( Addz ) );


	D3DXMATRIX mDecWorld, mDecRot, mDecTran;
	D3DXMatrixRotationYawPitchRoll( &mDecRot, -AddRot.y, -AddRot.x, -AddRot.z );
	D3DXMatrixTranslation( &mDecTran, -AddPos.x, -AddPos.y, -AddPos.z );
	mDecWorld = mAddWorld * mDecTran * mDecRot;

	printf( "\n- 追加した移動/回転値を取り除いたワールド行列を計算後、ワールド行列から座標を取得 -\n" );
	printf( "mWorld : x = %f, y = %f, z = %f\n", mDecWorld._41, mDecWorld._42, mDecWorld._43 );

	printf( "- 追加した移動/回転値を取り除いたワールド行列を計算後、ワールド行列から回転を取得 -\n" );
	float Decx = atanf( mDecWorld._23 / mDecWorld._33 );
	float Decy = atanf( -( mDecWorld._13 * cosf( Decx ) ) / mDecWorld._33 );
	float Decz = atanf( mDecWorld._12 / mDecWorld._11 );
	printf( "Rot  : x = %f, y = %f, z = %f\n", D3DXToDegree( Decx ), D3DXToDegree( Decy ), D3DXToDegree( Decz ) );

	return 0;
}