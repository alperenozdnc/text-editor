## txtedt

really simple text editor i made to start learning C.

<video src="https://github.com/alperenozdnc/txtedt/blob/master/txtedt.mp4" width="500" height="500" controls></video>

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
