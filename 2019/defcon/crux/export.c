#define MAX_ENV 0x10
#define ENV_SIZE 0x200

char env_list[ENV_SIZE * MAX_ENV];
char **var_list;

void export(char *buff, int readBytes) {
  int i, j, k, l, m;
  int x, y;

  /* split the argument by '=' */
  char *left = (char*)((unsigned long)buff + strlen("export "));
  for(i = 0; i < strlen(left); i++) {
    if (left[i] == '=') {
      char *right = &left[i + 1];
      left[i] = 0;
      break;
    }
  }

  x = 0;

  /* Is the variable already registered? */
  for(i = 0; i < MAX_ENV; i++) {
    c = 0;
    
    if (strlen(env_list[ENV_SIZE * i]) == 0) {
      // Not allocated
      continue;
    }
    if (strcmp(env_list[ENV_SIZE * i], left) == 0) {
      // Not this one
      continue;
    }

    /* Found the variable already registered */
    //ERROR
    readBytes -= strlen(left) + /*-*/ strlen("export"); // (value length) + 1

    /* Now let's see if the right expression is a variable or a value */
    for(j = 0; j < readBytes; j++, c++) { // why c++ necessary?
      if (right[j] == '$') {
	// It's a variable
	// Then, which variable is it?
	for(k = 0; k < MAX_ENV; k++) {
	  if (strncmp(right[j+1], env_list[ENV_SIZE*k], strlen(env_list[ENV_SIZE*k])) != 0) {
	    // Not this one
	    continue;
	  }
	  /* Found the variable referenced by $xxx */
	  // Copy the variable from k to i
	  for(l = 0; l < strlen(var_list[k])) {
	    var_list[i][c++] = var_list[k][l];
	  }

	  j += strlen(var_list[k]); // what's this?
	  break;
	}
      }
      
      var_list[j][c] = right[j]; // what's this?
    }
    
    break;
  }

  /* ? */
  if (x != 0) {
    return 0;
  }

  /* Allocate the variable to the freed chunk */
  for(i = 0; i < 0x10; i++) {
    c = 0;
    
    if (strlen(env_list[ENV_SIZE * i]) != 0) {
      // Occupied
      continue;
    }
    // Copy variable name
    memcpy(env_list[ENV_SIZE * i], left, strlen(left));
    
    // Allocate value region
    var_list[i] = malloc(ENV_SIZE - strlen(left) - strlen("export ") + 1);
    readBytes = 0x200 - strlen(left) - strlen("export ");

    /* Same as the code above */
    for(j = 0; j < readBytes; j++, c++) {
      if (right[j] == '$') {
	for(k = 0; k < MAX_ENV; k++) {
	  if (strncmp(right[j + 1], env_list[ENV_SIZE*k], strlen(env_list[ENV_SIZE*k])) != 0) {
	    break;
	  }

	  for(l = 0; l < strlen(var_list[k]); l++) {
	    var_list[i][c++] = var_list[k][l];
	  }

	  j += strlen(var_list[k]);
	  break;
	}
      }

      var_list[m][c] = right[c];
    }

    break;
  }

  // Bye
}
