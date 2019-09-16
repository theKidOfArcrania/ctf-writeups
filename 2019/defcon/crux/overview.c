
int do_command(char *buff, )
{
  int len = strlen(buff);
  if (len > 0x200) {
    return -1;
  }

  if (buff[len - 1] == '\n') {
    buf[len - 1] = 0;
  }

  if (strcmp(buff, "help") == 0) {
    
    sys_write("help text TODO!");
    
  } else if (strcmp(buff, "ls") == 0) {
    
    sys_ls(0);
    
  } else if (strcmp(buff, "id") == 0) {
    
    sys_write("uid=0(root) gid=0(wheel) groups=0(wheel)");
    
  } else if (strncmp(buff, "cat ", strlen("cat ")) == 0) {

    if (strlen(buff) > 4) {
      if (stristr(buff + 4, "honcho") == 0) {
	// argument doesn't have 'honcho'
	sys_write_file(buff + 4);
      } else {
	// argument has 'honcho'
	sys_write("reading hypervisor blocked by kernel!!");
      }
    } else {
      sys_write("no file to cat");
    }
    
  } else if (strncmp(buff, "export ", strlen("export ")) == 0) {

    int i, j, k, l, m;
    // ex)
    // export foo=bar
    // => left->foo / right->bar
    char *left = buff + strlen("export ");
    for(i = 0; i < strlen(left); i++) {
      if (left[i] == '=') {
	char *right = &left[i + 1];
	left[i] = 0;
	break;
      }
    }

    /* Find env key */
    for(j = 0; j < 0x10; j++) {
      wtf = 0;
      if (strlen(global_env[j * 0x200]) != 0) {
	if (strcmp(global_env[j * 0x200], left) == 0) {
	  result -= strlen(left) - strlen("export"); // ?
	  
	  ofs = 0;
	  for(ofs = 0; ofs < result; ofs++, wtf++) {
	    if (ofs < result) {
	      if (right[ofs] == '$') {
		// resolve $xxx
		for(k = 0; k < 0x10; k++) {
		  if (strncmp(right[ofs + 1],
			      global_env[k * 0x200],
			      strlen(global_env[k * 0x200])) == 0) {
		    // found $xxx
		    for(l = 0; l < strlen(large cs:4650h + k*8); l++) {
		      (large cs:4650h + j*8)[wtf++] = (large cs:4650h + k*8)[l];
		    }
		    ofs += strlen(large cs:4650h + k*8);
		    break;
		  }
		}
	      }
	      // finally
	      (large cs:4650h + j*8)[wtf] = right[ofs];
	    }
	  }
	}
      }
    }

    // alloc
    for(m = 0; m < 0x10; m++) {
      if (strlen(global_env[m * 0x200]) == 0) {
	memcpy(global_env[m * 0x200], left, strlen(left));
	(large cs:4650h + mz*8) = malloc(0x200 - strlen(left) - strlen("export ") + 1);
	result = 0x200 - strlen(left) - strlen("export ");
	for(ofs2 = 0; ofs2 < result; wtf2++, ofs2++) {
	  if (right[ofs2] == '$') {
	    for(k = 0; k < 0x10; k++) {
	      if (strncmp(right[ofs2 + 1],
			  global_env[k * 0x200],
			  strlen(global_env[k * 0x200])) == 0) {
		for(l = 0; l < strlen(large cs:4650h + k*8); l++) {
		  (large cs:4650h + m*8)[wtf2++] = (large cs:4650h + k*8)[l];
		}
		ofs2 += strlen(large cs:4650h + k*8);
		break;
	      }
	    }
	  }
	  // finally
	  (large cs:4650h + m*8)[wtf2] = right[ofs2];
	}
	break;
      }
    }
    
  } else if (strcmp(buff, "env") == 0) {

    int j;
    for(j = 0; j < 0x10; j++) {
      if (strlen(global_env[j * 0x200]) != 0) {
	put_str(global_env[j * 0x200]);
	put_str("=");
	put_str(large cs:4650h + j * 8); // value?
	put_str("\n");
      }
    }
    
  } else if (strcmp(buff, "exit") == 0) {
    
    sys_exit(0);
    
  } else if (strncmp(buff, "unset ", strlen("unset ")) == 0) {

    char *arg = buff + 6;
    int j;
    for(j = 0; j < 0x10; j++) {
      if (strlen(global_env[j * 0x200]) != 0) {
	if (strcmp(global_env[j * 0x200], arg) == 0) {
	  global_env[j * 0x200] = 0;
	  free(large cs:4650h + j * 8); // value?
	}
      }
    }
    
  } else {
    
    sys_write("command not found, press \"help\" for help!");
    
  }
}

void _start(void)
{
  while(1) {
    memset(buff, 0x200, 0);
    prompt();
    a2 = sys_read_input(buff, 0x1ff);
    do_command(buff, a2);
  }
}
