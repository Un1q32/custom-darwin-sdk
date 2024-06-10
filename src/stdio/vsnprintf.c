#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  size_t i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      size_t argstrlen;
      const char *fmt = format + i + 1, *fmt2 = format + i;
      bool done = false, altform = false;
      unsigned int fill = 0, percision = 6, flags = 0;
      char fillchar = ' ';
      while (!done) {
        if (*fmt == '#')
          altform = true;
        else if (*fmt == '.') {
          if (fmt[1] == '*') {
            percision = va_arg(ap, int);
            fmt++;
          } else {
            const char *strstart = fmt + 1, *strend = fmt + 1;
            while (isdigit(*strend))
              strend++;
            char percisionstr[strend - strstart + 1];
            memcpy(percisionstr, strstart, strend - strstart);
            percisionstr[strend - strstart] = '\0';
            percision = atoi(percisionstr);
            fmt = strend - 1;
          }
        } else if (*fmt == '0')
          fillchar = '0';
        else if (isdigit(*fmt)) {
          const char *strstart = fmt, *strend = fmt + 1;
          while (isdigit(*strend))
            strend++;
          char fillstr[strend - strstart + 1];
          memcpy(fillstr, strstart, strend - strstart);
          fillstr[strend - strstart] = '\0';
          fill = atoi(fillstr);
          fmt = strend - 1;
        } else if (*fmt == '*')
          fill = va_arg(ap, int);
        else {
          fmt--;
          done = true;
        }
        fmt++;
      }
      done = false;
      while (!done) {
        switch (*fmt++) {
        case 'l':
          if (flags & 1 << 0)
            flags |= 1 << 1;
          else
            flags |= 1 << 0;
          break;
        case 'h':
          if (flags & 1 << 2)
            flags |= 1 << 3;
          else
            flags |= 1 << 2;
          break;
        case 'j':
          flags |= 1 << 4;
          break;
        case 't':
          flags |= 1 << 5;
          break;
        case 'z':
          flags |= 1 << 6;
          break;
        case 'L':
          flags |= 1 << 7;
          break;
        case 'q':
          flags |= 1 << 8;
          break;
        default:
          fmt--;
          done = true;
          break;
        }
      }
      char *tmp = NULL;
      size_t k = 0;
      switch (*fmt) {
      case '%':
        if (j < size)
          str[j] = '%';
        j++;
        break;
      case 'S':
        flags |= 1 << 0;
        /* fall through */
      case 's':
        tmp = va_arg(ap, char *);
        if (tmp == NULL)
          tmp = "(null)";
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        break;
      case 'C':
        flags |= 1 << 0;
        /* fall through */
      case 'c':
        if (fill > 1) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        if (j < size)
          str[j] = va_arg(ap, int);
        j++;
        break;
      case 'd':
      case 'i':
        if (flags & 1 << 4)
          tmp = _itoa(va_arg(ap, intmax_t));
        else if (flags & 1 << 8)
          tmp = _itoa(va_arg(ap, quad_t));
        else if (flags & 1 << 1)
          tmp = _itoa(va_arg(ap, long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = _itoa(va_arg(ap, ptrdiff_t));
        else if (flags & 1 << 0)
          tmp = _itoa(va_arg(ap, long));
        else if (flags & 1 << 2)
          tmp = _itoa((short)va_arg(ap, int));
        else if (flags & 1 << 3)
          tmp = _itoa((char)va_arg(ap, int));
        else
          tmp = _itoa(va_arg(ap, int));
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'u':
        if (flags & 1 << 4)
          tmp = _utoa(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = _utoa(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = _utoa(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = _utoa(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = _utoa(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = _utoa((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = _utoa((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = _utoa(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'F':
      case 'f':
        if (flags & 1 << 7)
          tmp = _ftoa(va_arg(ap, long double), percision);
        else
          tmp = _ftoa(va_arg(ap, double), percision);
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'p':
        altform = true;
        flags |= 1 << 0;
        /* fall through */
      case 'x':
        if (flags & 1 << 4)
          tmp = _utox(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = _utox(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = _utox(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = _utox(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = _utox(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = _utox((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = _utox((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = _utox(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        if (altform) {
          if (j < size)
            str[j] = '0';
          j++;
          if (j < size)
            str[j] = 'x';
          j++;
        }
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'X':
        if (flags & 1 << 4)
          tmp = _utoX(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = _utoX(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = _utoX(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = _utoX(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = _utoX(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = _utoX((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = _utoX((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = _utoX(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        if (altform) {
          if (j < size)
            str[j] = '0';
          j++;
          if (j < size)
            str[j] = 'X';
          j++;
        }
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'n':
        if (flags & 1 << 4)
          *va_arg(ap, uintmax_t *) = j;
        else if (flags & 1 << 8)
          *va_arg(ap, u_quad_t *) = j;
        else if (flags & 1 << 1)
          *va_arg(ap, unsigned long long *) = j;
        else if (flags & 1 << 5 || flags & 1 << 6)
          *va_arg(ap, size_t *) = j;
        else if (flags & 1 << 0)
          *va_arg(ap, unsigned long *) = j;
        else if (flags & 1 << 2)
          *va_arg(ap, unsigned short *) = j;
        else if (flags & 1 << 3)
          *va_arg(ap, unsigned char *) = j;
        else
          *va_arg(ap, unsigned int *) = j;
        break;
      default:
        fmt--;
        break;
      }
      i += fmt - fmt2 + 1;
    } else {
      if (j < size)
        str[j] = format[i];
      j++;
      i++;
    }
  }
  if (j < size)
    str[j] = '\0';
  else if (size > 0)
    str[size - 1] = '\0';
  return j;
}
