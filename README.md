# GET_Next_Line
School project for Hive Helsinki. Small utility to return individual lines
allocated from a supplied file descriptor. Intended for parsing files in bigger projects.

## Installation / Usage
**NOTE:** requires `libft` for the linked list struct and some `ft_`-functions!

Include the provided header in your project and compile with the source file and in your
code, call the `get_next_line (int fd, char **line)` function.
It returns `RET_READL` on succesful line read, `RET_EOL` **after** the last line was read, or `RET_ERROR` upon error.

The user is expected to supply
a valid file descriptor and address of a string, as well as take care of freeing it after each call.

Minimal example:
```
int gnl_code;
while ((gnl_code = get_next_line (fd, &str)) == RET_READL)
{
  // what you want to do for each line here
  free (*str);
}
free (*str);
```
## Implementation
Our GNL uses a static reader struct behind the scenes which allocates linked list items while reading lines,
allowing it to read arbitrarily long lines despite the fixed buffer size. After each read it searches for the first newline
character and allocates a new string concatenating all the separate buffers into one sequence, this string is assinged to `line`.
Then it clears all the buffers except for the last one if there's still unscanned text left.

It does not, but could be made to support multiple simultaneous file descriptions,
and there is some more room for speed improvement, mainly eliminating the strcpy of the buffer tail after each newline.
