{ github.com/footballhead }
{ prints ENCONTER.SET in a human-readable way }
{ as a tab-delimited CSV }
program EncounterPrinter;
type
  EncounterData = record
    icon : byte;
    ai : byte;
    stackSize : byte;
    x : byte;
    y : byte;
    dialog1 : string[70];
    dialog2 : string[70];
  end;
var
  EncounterHandle : file of EncounterData;
  Encounter : EncounterData;
begin
  if ParamCount <> 1 then
  begin
    WriteLn('Usage: ENCONTER.EXE ENCONTER.SET');
    Halt(1);
  end;
  Assign(EncounterHandle, ParamStr(1));
  {$i-}
  Reset(EncounterHandle);
  {$i+}
  if IOResult <> 0 then
  begin
    WriteLn('Could not open file: ', ParamStr(1));
    Halt(1);
  end;
  WriteLn('Icon'#9'AI'#9'Stack Size'#9'X'#9'Y'#9'Dialog 1'#9'Dialog 2');
  repeat
    Read(EncounterHandle, Encounter);
    Write(Encounter.icon);
    Write(#9);
    Write(Encounter.ai);
    Write(#9);
    Write(Encounter.stackSize);
    Write(#9);
    Write(Encounter.x);
    Write(#9);
    Write(Encounter.y);
    Write(#9);
    Write(Encounter.dialog1);
    Write(#9);
    WriteLn(Encounter.dialog2);
  until Eof(EncounterHandle);
  Close(EncounterHandle);
end.
