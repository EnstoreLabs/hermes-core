/*
* Copyright (c) 2017 Cossack Labs Limited
*
* This file is a part of Hermes-core.
*
* Hermes-core is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Hermes-core is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Hermes-core.  If not, see <http://www.gnu.org/licenses/>.
*
*/



#include <hermes/mid_hermes_ll/interfaces/credential_store.h>
#include <string.h>
#include "../utils/utils.h"
#include <assert.h>

#define CREDENTIAL_STORE_PATH "db/credential_store"
#define CS_SUCCESS 0
#define CS_FAIL 1

struct hermes_credential_store_type{
  char path[1024];
};

hermes_credential_store_t* hermes_credential_store_create(void){
  hermes_credential_store_t* cs=calloc(1, sizeof(hermes_credential_store_t));
  assert(cs);
  memcpy(cs->path, CREDENTIAL_STORE_PATH, strlen(CREDENTIAL_STORE_PATH)+1);
  create_directory(cs->path);
  return cs;
}

hermes_status_t hermes_credential_store_get_public_key(hermes_credential_store_t* cs, const uint8_t* user_id, const size_t user_id_length, uint8_t** pub_key, size_t* pub_key_length){
  char fpath[10*1024];
  BUILD_TYPED_PATH(fpath, C(cs->path), E(user_id, user_id_length));
  return read_whole_file(fpath, pub_key, pub_key_length);  
}

hermes_status_t hermes_credential_store_destroy(hermes_credential_store_t** cs){
  if(!cs || !(*cs)){
    return CS_FAIL;
  }
  free(*cs);
  *cs=NULL;
  return CS_SUCCESS;
}

