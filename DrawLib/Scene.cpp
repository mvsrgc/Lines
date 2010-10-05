#include "Scene.h"
#include "Node.h"
#include "ImageSprite.h"
#include "drwCursor.h"
#include <QImage>

Scene::Scene( QObject * parent )
: QObject( parent )
{
	m_cursor = new drwCursor;
	m_cursorVisible = false;
}

Scene::~Scene()
{
	// Delete all images
	for( unsigned i = 0; i < m_imageDb.size(); ++i )
	{
		delete m_imageDb[i].Sprite;
	}
	m_imageDb.clear();
	delete m_cursor;
}

void Scene::Clear()
{
	for( unsigned i = 0; i < Frames.size(); ++i )
		Frames[i].Clear();
	AlwaysDisplayed.Clear();
}

void Scene::DrawPersistent( const drwDrawingContext & context )
{
	AlwaysDisplayed.Draw( context );
}

void Scene::DrawFrame( int frame, const drwDrawingContext & context )
{
	if( frame < (int)Frames.size() && frame >= 0 )
		Frames[ frame ].Draw( context );
}


void Scene::AddNode( Node * node )
{
	m_nodesMutex.lock();
	AlwaysDisplayed.AddNode( node );
	m_nodesMutex.unlock();
}


void Scene::AddNodeToFrame( Node * node, int frame )
{
	if( frame >= 0 && frame < (int)Frames.size() )
	{
		m_nodesMutex.lock();
		Frames[ frame ].AddNode( node );
		m_nodesMutex.unlock();
	}
}

Node * Scene::GetNodeById( int frame, GLuint Id )
{
	Node * ret = AlwaysDisplayed.GetNodeById( Id );
	if( !ret )
		ret = Frames[ frame ].GetNodeById( Id );
	return ret;
}

void Scene::SetNumberOfFrames( int nbFrames )
{
	Frames.resize( nbFrames );
	emit NumberOfFramesChanged( nbFrames );
}

void Scene::InsertFrame( int beforeThisFrame )
{
	if( beforeThisFrame <= (int)Frames.size() )
	{
		std::vector<Frame>::iterator it = Frames.begin();
		if( beforeThisFrame == (int)Frames.size() )
			it = Frames.end();
		else
			it += beforeThisFrame;
		Frame newFrame;
		Frames.insert( it, newFrame );
		emit NumberOfFramesChanged( Frames.size() );
	}
}

void Scene::MarkModified()
{
	emit Modified();
}

ImageSprite * Scene::GetImageSprite( const char * filename )
{
	// See if a sprite with same filename already exists
	for( unsigned i = 0; i < m_imageDb.size(); ++i )
	{
		if( m_imageDb[i].ImageFileName == filename )
		{
			return m_imageDb[i].Sprite;
		}
	}
	
	// It doesn't, try to load
	QImage im;
	if ( !im.load( filename ) )
		return 0;

	// Create the sprite
	ImageInfo info;
	info.ImageFileName = filename;
	info.Sprite = new ImageSprite;
	info.Sprite->SetImage( im );
	m_imageDb.push_back( info );
	
	return info.Sprite;
}

void Scene::DrawCursor( const drwDrawingContext & context )
{
	if( m_cursorVisible )
		m_cursor->Draw( context );
}

void Scene::SetCursorVisible( bool visible ) 
{ 
	if( visible != m_cursorVisible )
	{
		m_cursorVisible = visible;
		MarkModified();
	}
}
