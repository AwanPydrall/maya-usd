//
// Copyright 2017 Animal Logic
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#pragma once

#include "maya/MPxCommand.h"
#include "AL/maya/utils/MayaHelperMacros.h"

namespace AL {
namespace usdmaya {
namespace cmds {

//----------------------------------------------------------------------------------------------------------------------
/// \brief   A command that allows you to register and unregister new Event types from script.
/// \ingroup commands
//----------------------------------------------------------------------------------------------------------------------
class CreateUsdPrim
  : public MPxCommand
{
public:
  AL_MAYA_DECLARE_COMMAND();
private:
  MStatus doIt(const MArgList& args) override;
};

} // cmds
} // usdmaya
} // AL
