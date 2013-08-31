
#include <iostream>
/* NOT SURE IF WE NEED THIS ... BUT IT COULD NOT FIND MUTLTI TEXTURE SHIT WITHOUT IT */
#define GL_GLEXT_LEGACY 1


#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <cstdlib>

#include "SDL.h"

//#include "Object.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Plane.h"
#include "AxisAlignedBoundingBox.h"
#include "Axis.h"
#include "Triangle.h"
#include "Sphere.h"
using namespace Affine;


/* This is our SDL surface */
SDL_Surface *surface;

Vector test;
Point center;
Vector up;
Point eye;
//RadiositySolver *rad;
//Octree::Node *oct;
//RayTracer tracer;

bool rotate = false;

GLuint texture[1]; /* Storage For One Texture ( NEW ) */
bool	marglar = false;
 

/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode ){
    SDL_Quit( );
    exit( returnCode );
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height ){
    float ratio;

    if ( height == 0 )height = 1;
    ratio = ( GLfloat )width / ( GLfloat )height;
    glViewport( 0, 0, ( int )width, ( int )height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 90.0f, ratio, 0.1f, 100.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    return( 1 );
}
// function to handle mouse motion events 
// 
// Uses the relative coords.
// Top left of screen is 0,0
// bottom right is width,height
void handleMouseMotion( SDL_MouseMotionEvent *event ) {
	//Ignore huge jumps.
	if( event->xrel > 50 ) return;
	if( event->yrel > 50 ) return;
	//Deal with the rest
}
/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:	 
	    Quit( 0 );
	    break;
	case SDLK_F1:
//		camera.lookAt( eye, center, up );
	    break;
	case SDLK_F2:
		
		break;
	case SDLK_F3:
//	    camera.lookRight();
	    break;	
	case SDLK_F4:
//	    camera.lookUp();
	    break;		
	case SDLK_F5:
		break;	
	case SDLK_F6:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
		glDisable( GL_TEXTURE_2D );
		break;
	case SDLK_F7:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_TEXTURE_2D );
		break;	
	case SDLK_F8:
		break;
	case SDLK_F10:
		break;
	case SDLK_F11:
		break;
	case SDLK_F12:
		break;				
	case SDLK_UP:
//		camera.calculateFirstPersonMatrix(0, 0, 2);		
		break;
	case SDLK_DOWN:
//		camera.calculateFirstPersonMatrix(0, 0, 1);
		break;
	case SDLK_LEFT:
//		camera.calculateFirstPersonMatrix(0, 0, 4);
		break;
	case SDLK_RIGHT:
//		camera.calculateFirstPersonMatrix(0, 0, 3);
		break;	
	default:
	    break;
	}

    return;
}
unsigned int txt;

/* general OpenGL initialization function */
int initGL( GLvoid )
{

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );   
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glDepthFunc( GL_LEQUAL );
    glCullFace(GL_BACK);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    GLfloat light0_position[] = { 100.0, 100.0, 100.0, 0.0 };
    GLfloat light1_position[] = { -100.0, 100.0, 100.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    
	
	//glEnable(GL_TEXTURE_2D);							// enable texturing
	glActiveTextureARB(GL_TEXTURE0_ARB);				// texture bank

	glEnable(GL_TEXTURE_2D);							// enable texturing
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT );
    glTexEnvf( GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE );
	

	glActiveTextureARB(GL_TEXTURE1_ARB);				// lightmap bank	

	glEnable(GL_TEXTURE_2D);							// enable texturing
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT );
    glTexEnvf( GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_BLEND );
	
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

		
    center.set(0.0f, 0.0f, 0.0f);
    eye.set(0.0f, 0.0f, 1.0f);
    up.set( 0.0, 1.0, 0.0 );


    glPointSize( 5.0f );
	

    return( 1 );
}

/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
    /* These are to calculate our fps */
    static int T0     = 0;
    static int Frames = 0;	
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();	


    
  
	
    

	//	glLoadMatrixf( camera.getModelViewMatrix() );
		//glColor3f(1.0f, 1.0f, 1.0f);
		//g->render();
		
		/*
		glBegin(GL_TRIANGLES);
			glVertex3f( tri[0][0], tri[0][1], tri[0][2] );
			glVertex3f( tri[1][0], tri[1][1], tri[1][2] );
			glVertex3f( tri[2][0], tri[2][1], tri[2][2] );
		glEnd();
		
		Point *ref = sloot[10];
		Ray r( *ref, tri.myNormal );
		Point end = r.getPointFromScaler( 5.0f );
		glBegin( GL_LINES );			
			glVertex3f( (*ref)[0], (*ref)[1], (*ref)[2] );	
			glVertex3f( end[0], end[1], end[2] );
		glEnd();
		*/
		

    /* Draw it to the screen */
	glFlush();
    SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
   	Frames++;
    {
		GLint t = SDL_GetTicks();
		if (t - T0 >= 5000) {
	   		GLfloat seconds = (t - T0) / 1000.0;
	    	GLfloat fps = Frames / seconds;
	    	printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    	T0 = t;
	    	Frames = 0;
		}
    }
    return( 1 );
}

int main( int argc, char **argv )
{
    /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    int done = 0;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    int isActive = 1;

	if( argc != 2) {
		std::cerr << "Please specify model\n";
		return 0;
	}
	
    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    fprintf( stderr, "Video initialization failed: %s\n",SDL_GetError( ) );
	    Quit( 1 );
	}

    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, videoFlags );

    /* Verify there is a surface */
    if ( !surface ){
	fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	Quit( 1 );
    }

    /* initialize OpenGL */
    initGL( );
    /* resize the initial window */
    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );
    /* wait for events */
    while ( !done )
	{
	    /* handle the events in the queue */

	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			    if ( event.active.gain == 0 )
				isActive = 0;
			    else
				isActive = 1;
			    break;			    
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    surface = SDL_SetVideoMode( event.resize.w, event.resize.h, 32, videoFlags );
			    if ( !surface ){
			    	    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
				    Quit( 1 );
			    }
			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_MOUSEMOTION:
				handleMouseMotion( &event.motion );
				break;
			case SDL_MOUSEBUTTONDOWN:
				rotate = true;
				break;
			case SDL_MOUSEBUTTONUP:
				rotate = false;
				break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = 1;
			    break;
			default:
			    break;
			}
		}
	    /* draw the scene */
		drawGLScene( );
	}
    /* clean ourselves up and exit */
    Quit( 0 );
    /* Should never get here */
    return 0;
}
