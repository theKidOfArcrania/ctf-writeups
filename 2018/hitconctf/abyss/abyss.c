void *__fastcall commands(char cmd)
{
  void *result; // rax

  switch ( (unsigned int)off_11CC )             // cmd
  {
    case '$':
      result = dup_;
      break;
    case '%':
      result = pop_;
      break;
    case '&':
      result = and_;
      break;
    case '*':
      result = mul;
      break;
    case '+':
      result = add;
      break;
    case ',':
      result = write_;
      break;
    case '-':
      result = minus;
      break;
    case '.':
      result = writed;
      break;
    case '/':
      result = div_;
      break;
    case ':':
      result = store; //pop ind, pop val
      break;
      case ';':
      result = fetch; //pop ind, push val
      break;
    case '=':
      result = eql;
      break;
    case '>':
      result = gt;
      break;
    case '@':
      result = rot;
      break;
    case '\\':
      result = swap_;
      break;
    case '_':
      result = neg;
      break;
    case '|':
      result = or_;
      break;
    case '~':
      result = not_;
      break;
    default:
      result = 0LL;
      break;
  }
  return result;
}
