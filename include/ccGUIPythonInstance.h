//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: PythonPlugin                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                   COPYRIGHT: Thomas Montaigu                           #
//#                                                                        #
//##########################################################################

#ifndef CLOUDCOMPAREPROJECTS_CCGUIPYTHONINSTANCE_H
#define CLOUDCOMPAREPROJECTS_CCGUIPYTHONINSTANCE_H

#include <FileIOFilter.h>
#include <ccMainAppInterface.h>

/// This class provide methods that are made available Python scripts
/// kind of like C++ plugins have access to a `ccMainAppInterface`.
/// Thus this class is mostly a ccMainAppInterface with some accommodations
/// to handle the fact that it is made to interact with python.
class Q_DECL_EXPORT ccGUIPythonInstance
{
  public:
    explicit ccGUIPythonInstance(ccMainAppInterface *app);

    QMainWindow * getMainWindow() {
        return m_app->getMainWindow();
    }

    bool haveSelection() const { return m_app->haveSelection(); }

    bool haveOneSelection() const { return m_app->haveOneSelection(); }

    const ccHObject::Container &getSelectedEntities() const { return m_app->getSelectedEntities(); }

    void setSelectedInDB(ccHObject *obj, bool selected) { m_app->setSelectedInDB(obj, selected); }

    ccHObject *dbRootObject() { return m_app->dbRootObject(); }

    void addToDB(ccHObject *obj,
                 bool updateZoom = false,
                 bool autoExpandDBTree = true,
                 bool checkDimensions = false,
                 bool autoRedraw = true);

    void redrawAll(bool only2D = false) { return m_app->redrawAll(only2D); }

    void refreshAll(bool only2D = false) { return m_app->refreshAll(only2D); }

    void enableAll() { return m_app->enableAll(); }

    void disableAll() { return m_app->disableAll(); }

    void updateUI() { return m_app->updateUI(); }

    void freezeUI(bool state) { return m_app->freezeUI(state); }

    ccHObject *createObject(const char *type_name);

    ccHObject *loadFile(const char *filename, FileIOFilter::LoadParameters &parameters);

    /// Clears the internal database of objects that were allocated on the python side
    /// but were not added to the DB tree via `addToDB`
    size_t clearDB();

  private:
    ccMainAppInterface *m_app;
    // This holds pointer to objects that were created by a Python script.
    // They are kept in this vector until they are either moved to the true ccDB (using `addToDB`)
    // or when `clearDB` is called (which is a method not exposed to the python side
    // and the c++ takes care of calling the `clearDB` fn when appropriate).
    std::vector<ccHObject *> m_pythonDB;
};

#endif // CLOUDCOMPAREPROJECTS_CCGUIPYTHONINSTANCE_H
