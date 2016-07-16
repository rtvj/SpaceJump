#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <sys/stat.h>
#include "CSCIx229.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>


#define MAX_VERTICES    8000 // Max number of vertices (for each object)
#define MAX_POLYGONS    8000 // Max number of polygons (for each object)
#define NUM_PARTICLES   500          /* Number of particles  */
#define NUM_DEBRIS      700            /* Number of debris     */
#define NUM_STAR        300
#define SH              5000

// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];

	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
} obj_type, *obj_type_ptr;

// music
Mix_Music* blt;
Mix_Music* eng;
Mix_Music* blast;


typedef struct                       /**** BMP file info structure ****/
    {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    char *data;
    } BITMAPINFOHEADER;

/* A particle */

struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
};
typedef struct particleData    particleData;

struct Star
{
  double   x;
  double   y;
  double   z;
  float a;
  float b;
  float c;

};
typedef struct Star    Star;


/* A piece of debris */
struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};
typedef struct debrisData    debrisData;

int road_x = 0;
int road_y = 0;
int road_z = 0;
int wall_x = 0;
int wall_y = -10;
int wall_z = -6000;
double Ux = 1;   //  Up
double Uy = 0;   //  Up
double Uz = 0;   //  Up
double Ox = 0;   //  LookAt
double Oy = 0;   //  LookAt
double Oz = 0;   //  LookAt
double Ex = 1;   //  Eye
double Ey = 1;   //  Eye
double Ez = 1;   //  Eye
double X  = 0;   //  Location
double Y  = 0;   //  Location
double Z  = 0;   //  Location
double Dx = 1;   //  Direction
double Dy = 0;   //  Direction
double Dz = 0;   //  Direction
int    th=0;     //  Azimuth of view angle
int    ph=0;     //  Elevation of view angle
int    zh=0;     //  Azimuth of light
int    move=0;   //  Light movement
int jump = 0;   // make a jump
int descend = 0;  // descend from a jump
int gravity = 0;  // gravity actively pulling down
double dim=1500.0;  //  Size of world
static int px = 0;  // spaceship x coordinate
static int py = -10;  // spaceship y coordinate
static int pz = 1800;  // spaceship z coordinate
double ll = -10; // bullet firing distance
int bx;	// bullet x coordinate
int by;	// bullet y coordinate
int bz;	// bullet z coordinate
int bullet = 0; // bullet present variable
int enemy = 1;	// enemy present variable
int space = 1;	// spaceship present variable
int ex = 100, ey = -10, ez = -6000; // enemy coordinate variable
int prs = 75;  // precision
double side = 0;  // horizontal movement variable
double up = 0; // vertical movement variable
int fx = 0, fy = 0, fz = -12;
float rep = 1.0;
// The width and height of your window, change them as you like
int screen_width=1280;
int screen_height=720;
int	sky[2];   //  Sky textures
int zz[20] ;
float ty = SH;
int ii=0;
int score = 0, flag1 = 0, flag2 = 0, flag3 = 0;
int width, height;
int enter = 1;
// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;

// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

particleData     particles[NUM_PARTICLES];
Star     star[NUM_STAR];
debrisData       debris[NUM_DEBRIS];
int              fuel = 0;                /* "fuel" of the explosion */

float            angle = 0.0;             /* camera rotation angle */
unsigned int texture[4]; // Texture names

int num_texture=-1;
int      wantNormalize = 0;   /* Speed vector normalization flag */
int      wantPause = 0;       /* Pause flag */
obj_type object;
int ov = 0, over = 0;


char Load3DS (obj_type_ptr ogg, char *filename);
int LoadBitmap(char *filename);
unsigned int LoadTexBMP(const char* file);
static void Reverse(void* x,const int n);
void mover(int toggle);
void CreateExplosion(void);
void Speed (float dest[3]);
void stars(double x, double y, double z, float a, float b, float c);
void Init_star(void);
void Road(double xx, double yy, double zz);
void show_tex(void);
void laser_bullet(double x,double y,double z, double dx,double dy,double dz);
void spaceship(double px, double py, double pz,	double dx, double dy, double dz, double sx, double sy, double sz);
void update_animation(void);
void glWindowPos2i(GLint  x,  GLint  y);
void SwitchGameplay(int i);


