#include "ProfileDescription.h"

ProfileDescription::ProfileDescription(int userID , string about, bool visibility)
    :about(about), visibility(visibility) {
}
ProfileDescription::ProfileDescription()
    :about(""), visibility(false) {
}  
