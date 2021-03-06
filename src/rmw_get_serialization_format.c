// Copyright 2022 Washington University in St Louis
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

#include "rmw/rmw.h"

const char * const hazcat_serialization_format = "shared_memory";

#ifdef __cplusplus
extern "C"
{
#endif
const char *
rmw_get_serialization_format()
{
  return hazcat_serialization_format;
}
#ifdef __cplusplus
}
#endif
