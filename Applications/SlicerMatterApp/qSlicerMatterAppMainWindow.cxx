/*==============================================================================

  Copyright (c) Kitware, Inc.

  See http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware, Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// SlicerMatter includes
#include "qSlicerMatterAppMainWindow.h"
#include "qSlicerMatterAppMainWindow_p.h"

// Qt includes
#include <QDesktopWidget>

// Slicer includes
#include "qSlicerApplication.h"
#include "qSlicerAboutDialog.h"
#include "qSlicerMainWindow_p.h"
#include "qSlicerModuleSelectorToolBar.h"

//-----------------------------------------------------------------------------
// qSlicerMatterAppMainWindowPrivate methods

qSlicerMatterAppMainWindowPrivate::qSlicerMatterAppMainWindowPrivate(qSlicerMatterAppMainWindow& object)
  : Superclass(object)
{
}

//-----------------------------------------------------------------------------
qSlicerMatterAppMainWindowPrivate::~qSlicerMatterAppMainWindowPrivate()
{
}

//-----------------------------------------------------------------------------
void qSlicerMatterAppMainWindowPrivate::init()
{
  Q_Q(qSlicerMatterAppMainWindow);
  this->Superclass::init();
}

//-----------------------------------------------------------------------------
void qSlicerMatterAppMainWindowPrivate::setupUi(QMainWindow * mainWindow)
{
  qSlicerApplication * app = qSlicerApplication::application();

  //----------------------------------------------------------------------------
  // Add actions
  //----------------------------------------------------------------------------
  QAction* helpAboutSlicerAppAction = new QAction(mainWindow);
  helpAboutSlicerAppAction->setObjectName("HelpAboutSlicerMatterAppAction");
  helpAboutSlicerAppAction->setText("About " + app->applicationName());

  //----------------------------------------------------------------------------
  // Calling "setupUi()" after adding the actions above allows the call
  // to "QMetaObject::connectSlotsByName()" done in "setupUi()" to
  // successfully connect each slot with its corresponding action.
  this->Superclass::setupUi(mainWindow);

  //----------------------------------------------------------------------------
  // Configure
  //----------------------------------------------------------------------------
  mainWindow->setWindowIcon(QIcon(":/Icons/Medium/DesktopIcon.png"));

  QPixmap logo(":/LogoFull.png");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
  qreal dpr = sqrt(qApp->desktop()->logicalDpiX()*qreal(qApp->desktop()->logicalDpiY()) / (qApp->desktop()->physicalDpiX()*qApp->desktop()->physicalDpiY()));
  logo.setDevicePixelRatio(dpr);
#endif
  this->LogoLabel->setPixmap(logo);

  // Hide the toolbars
  this->MainToolBar->setVisible(false);
  //this->ModuleSelectorToolBar->setVisible(false);
  this->ModuleToolBar->setVisible(false);
  this->ViewToolBar->setVisible(false);
  this->MouseModeToolBar->setVisible(false);
  this->CaptureToolBar->setVisible(false);
  this->ViewersToolBar->setVisible(false);
  this->DialogToolBar->setVisible(false);

  // Hide the menus
  //this->menubar->setVisible(false);
  //this->FileMenu->setVisible(false);
  //this->EditMenu->setVisible(false);
  //this->ViewMenu->setVisible(false);
  //this->LayoutMenu->setVisible(false);
  //this->HelpMenu->setVisible(false);

  // Hide the modules panel
  //this->PanelDockWidget->setVisible(false);
  this->DataProbeCollapsibleWidget->setCollapsed(true);
  this->DataProbeCollapsibleWidget->setVisible(false);
  this->StatusBar->setVisible(false);
}

//-----------------------------------------------------------------------------
// qSlicerMatterAppMainWindow methods

//-----------------------------------------------------------------------------
qSlicerMatterAppMainWindow::qSlicerMatterAppMainWindow(QWidget* windowParent)
  : Superclass(new qSlicerMatterAppMainWindowPrivate(*this), windowParent)
{
  Q_D(qSlicerMatterAppMainWindow);
  d->init();
}

//-----------------------------------------------------------------------------
qSlicerMatterAppMainWindow::qSlicerMatterAppMainWindow(
  qSlicerMatterAppMainWindowPrivate* pimpl, QWidget* windowParent)
  : Superclass(pimpl, windowParent)
{
  // init() is called by derived class.
}

//-----------------------------------------------------------------------------
qSlicerMatterAppMainWindow::~qSlicerMatterAppMainWindow()
{
}

//-----------------------------------------------------------------------------
void qSlicerMatterAppMainWindow::on_HelpAboutSlicerMatterAppAction_triggered()
{
  qSlicerAboutDialog about(this);
  about.setLogo(QPixmap(":/Logo.png"));
  about.exec();
}
