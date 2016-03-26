#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Math/Vector3.h"
#include "GameLib/Math/Matrix34.h"
#include "GameLib/Math/Matrix44.h"
#include "GameLib/Math/Functions.h"
#include "GameLib/Scene/TriangleRenderer.h"
#include <sstream>
using namespace std;
using namespace GameLib::Math;
using namespace GameLib::Graphics;
using namespace GameLib::Scene;

int gCount;
TriangleRenderer gTriangleRenderer;

namespace GameLib{
	void Framework::configure(){
		setWidth( 640 );
		setHeight( 480 );
		enableFullScreen( false );
		enableVSync( true );
		setTitle( "DrawTriangle Sample" );
	}
	void Framework::update(){
		if ( gCount == 0 ){
			//�O�p�`�`��N���X��10�O�p�`�A10���߂ŏ�����
			gTriangleRenderer = TriangleRenderer( 10, 10 );
		}

		//���̒��_�z��
		Vector3 p[ 4 ];
		unsigned c[ 4 ]; //�킩��₷���悤�ɐF
		p[ 0 ].set( -1000.f, -1000.f, 0.f );
		p[ 1 ].set( -1000.f, 1000.f, 0.f );
		p[ 2 ].set( 1000.f, -1000.f, 0.f );
		p[ 3 ].set( 1000.f, 1000.f, 0.f );
		c[ 0 ] = 0xffff0000; //��
		c[ 1 ] = 0xff00ff00; //��
		c[ 2 ] = 0xff0000ff; //��
		c[ 3 ] = 0xffffffff; //��

		//���[���h�ϊ�(Z��])
		Matrix34 wm;
		wm.setRotationZ( gCount / 25.f );
		//�r���[�s�����낤
		Vector3 eyePosition;
		eyePosition.x = sin( gCount / 100.f ) * 4000.f;
		eyePosition.z = cos( gCount / 100.f ) * 4000.f;
		eyePosition.y = 1000.f;
		Vector3 eyeTarget( 0.f, 0.f, 0.f );
		Matrix34 vm;
		vm.setViewTransform( eyePosition, eyeTarget, Vector3( 0.f, 1.f, 0.f ) );
		//�����ϊ��s��
		Matrix44 pm;
		pm.setPerspectiveTransform( 
			PI/3.f, 
			static_cast< float >( getWidth() ),
			static_cast< float >( getHeight() ),
			1.f, 10000.f );
		//�܂�VW�����
		vm *= wm;
		//����PVW�����
		pm *= vm;
		//�s��Z�b�g
		gTriangleRenderer.setTransform( pm );
		//�l�p�`�𑫂�
		gTriangleRenderer.add( &p[ 0 ].x, &p[ 1 ].x, &p[ 2 ].x, 0, 0, 0, c[ 0 ], c[ 1 ], c[ 2 ] );
		gTriangleRenderer.add( &p[ 3 ].x, &p[ 1 ].x, &p[ 2 ].x, 0, 0, 0, c[ 3 ], c[ 1 ], c[ 2 ] );
		//�����I������̂ŕ`��
		gTriangleRenderer.draw();

		ostringstream oss;
		oss << "Framerate: " << getFrameRate();
		drawDebugString( 0, 0, oss.str().c_str() );

		++gCount;

		if ( isEndRequested() ){
			gTriangleRenderer.release(); //�O���[�o���Ȃ̂ŊJ���������K�v
		}
	}
}
