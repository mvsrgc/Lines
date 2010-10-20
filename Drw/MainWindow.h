#ifndef __MainWindow_h_
#define __MainWindow_h_

#include <QMainWindow>
#include <QString>

class QPopupMenu;
class QWorkspace;
class QPopupMenu;
class QDockWidget;

class drwDrawingWidget;
class Scene;
class drwLineTool;
class drwToolbox;
class drwCommandDatabase;
class PrimitiveToolOptionWidget;
class PlaybackControlerWidget;
class TabletStateWidget;
class DisplaySettingsWidget;
class PlaybackControler;
class drwCommandDispatcher;
class drwNetworkManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();
    ~MainWindow();
	
	void closeEvent( QCloseEvent * e );

private slots:
	
	void fileNew();
	void fileOpen();
	bool fileSave();
	void fileSaveAs();
	bool fileExport();
	
	void editSetNumberOfFrames();
	
	void NetShareSession();
	void NetConnect();
	
	void viewFullscreen();

    void about();
    void aboutQt();
	
protected:
	
	// Get global keyboard shortcuts
	bool eventFilter(QObject *obj, QEvent *event);
	
	// Construction utilities
	void CreateActions();

private:
	
	bool GetSaveFilename();
	bool maybeSave();
	void readSettings();
	void writeSettings();
	
	QString m_filename;
	QString m_fileDialogStartPath;
	
	QString m_exportDefaultPath;
	QSize m_exportRes;

	drwDrawingWidget    * m_glWidget;

	QMenu       * m_viewMenu;
	QMenu		* m_editMenu;
	QMenu		* m_networkMenu;
	
	PlaybackControlerWidget * m_playbackControlerWidget;
	
	PrimitiveToolOptionWidget * m_toolOptionWidget;
	QDockWidget * m_dockToolsOptions;
	
	DisplaySettingsWidget * m_displaySettingsWidget;
	QDockWidget * m_dockDisplayOptions;
		
	TabletStateWidget * m_tabletStateWidget;
	QDockWidget * m_dockTabletState;
	
	Scene						* m_scene;
	PlaybackControler			* m_controler;
	drwToolbox	* m_observer;
    drwCommandDatabase			* m_commandDb;
    drwCommandDispatcher * m_commandDispatcher;
    drwNetworkManager * m_networkManager;

    static const QString m_appName;
};


#endif
