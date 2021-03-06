// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <cctype>
#include <mvvm/interfaces/applicationmodelsinterface.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/project/project.h>
#include <mvvm/project/projectutils.h>
#include <mvvm/utils/fileutils.h>

using namespace ModelView;

namespace
{
const std::string json_extention = ".json";
const std::string untitled_name = "Untitled";
} // namespace

//! Suggests file name which can be used to store json content of given model.
//! Uses the model type to construct a filename: MaterialModel -> materialmodel.json

std::string ProjectUtils::SuggestFileName(const SessionModel& model)
{
    std::string result = model.modelType();
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result + json_extention;
}

//! Returns 'true' if given directory might be a project directory.
//! This simplified check counts number of files with json extention.

bool ProjectUtils::IsPossibleProjectDir(const std::string& project_dir)
{
    return !Utils::FindFiles(project_dir, json_extention).empty();
}

//! Creates new untitled project.

std::unique_ptr<ProjectInterface>
ProjectUtils::CreateUntitledProject(ApplicationModelsInterface* models,
                                    std::function<void()> project_changed_callback)
{
    return std::make_unique<Project>(models, project_changed_callback);
}

//! Returns a MainWindow title for given project.

std::string ProjectUtils::ProjectWindowTitle(const ProjectInterface& project)
{
    return ProjectWindowTitle(project.projectDir(), project.isModified());
}

//! Returns a title composed from last part of project path, and `is_modified` flag.
//! Project without projectDir will be "Untitled", modified project will be "*Untitled".
//! Project with projectDir in "/home/user/project1" will get title "project1".

std::string ProjectUtils::ProjectWindowTitle(const std::string& project_dir, bool is_modified)
{
    auto pos = project_dir.find_last_of("/");
    auto project_name = (pos == std::string::npos ? untitled_name : project_dir.substr(pos + 1));
    auto unsaved_status = is_modified ? "*" : "";
    return unsaved_status + project_name;
}
