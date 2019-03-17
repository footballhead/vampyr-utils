{ github.com/footballhead }
{ prints ENCONTER.SET in a human-readable way }
{ as a tab-delimited CSV }
program EncounterPrinter;
const
  EncounterFile = 'ENCONTER.SET';
  OutputFile = 'ENCONTER.CSV';
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
  OutputHandle : Text;
begin
  Assign(EncounterHandle, EncounterFile);
  Assign(OutputHandle, OutputFile);
  Reset(EncounterHandle);
  Rewrite(OutputHandle);
  WriteLn(OutputHandle, 'Icon'#9'AI'#9'Stack Size'#9'X'#9'Y'#9'Dialog 1'#9'Dialog 2');
  repeat
    Read(EncounterHandle, Encounter);
    Write(OutputHandle, Encounter.icon);
    Write(OutputHandle, #9);
    Write(OutputHandle, Encounter.ai);
    Write(OutputHandle, #9);
    Write(OutputHandle, Encounter.stackSize);
    Write(OutputHandle, #9);
    Write(OutputHandle, Encounter.x);
    Write(OutputHandle, #9);
    Write(OutputHandle, Encounter.y);
    Write(OutputHandle, #9);
    Write(OutputHandle, Encounter.dialog1);
    Write(OutputHandle, #9);
    WriteLn(OutputHandle, Encounter.dialog2);
  until Eof(EncounterHandle);
  Close(EncounterHandle);
  Close(OutputHandle);
end.
