## txtedt

really simple text editor i made to start learning C.

here is a [usage video](https://github.com/alperenozdnc/txtedt/releases/download/v1.0.0/txtedt.mp4).

### what i learned

this project helped me get ideas on:

- how to structure a C project,
- manual memory management,
- string manipulation,
- dealing with undefined behaviours (which i never used to deal with in high-level languages),
- how `make` can be utilized to increase project development speed,
- writing tests for C,
- pointers, references, deferences, structs, enums, etc...
- reading the manuals more carefully,

and much more.

### installation (linux only)

run `install.sh` to build the code and put it into the binaries.

### usage

```bash
$ txtedt {filename}
```

`<ctrl-h>` can be used for a shortcut list. \
`<ctrl-c>` exits the program.

### uninstallation

run `uninstall.sh` to remove the `txtedt` binary from `/usr/bin`.

### license

all content on `txtedt` is licensed under the GNU General Public License Version 3. read `LICENSE` for more details.
