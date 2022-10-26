.list
.symbols
.lstfile
.map
.mapfile
          org      0
num:      dw       -1
loop:     ldn      num                ; will actually load 1
          sto      var                ; write to destination
          sub      num                ; subtract -1, which adds 1
          jmp      [loop]             ; back to loop
          refs                        ; add reference table

          org      31
var:      dw       0

