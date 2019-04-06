{ prints MON.DAT as a tab-delimited CSV }
program MonsterDataPrinter;
type
  MonsterData = record
    displayName : string[15];
    life : smallint;
    xp : smallint;
    a : byte; { UNKNOWN }
    b : byte; { UNKNOWN }
    wpn : byte;
    arm : byte;
    maxSize : byte;
    c : byte; { UNKNOWN }
    d : byte; { UNKNOWN }
    ability : byte;
  end;
var
  InputHandle : file of MonsterData;
  Monster : MonsterData;
begin
  if ParamCount <> 1 then
  begin
    WriteLn('Usage: mondat MON.DAT');
    Halt(1);
  end;
  Assign(InputHandle, ParamStr(1));
  {$i-}
  Reset(InputHandle);
  {$i+}
  if IOResult <> 0 then
  begin
    WriteLn('Could not open file: ', ParamStr(1));
    Halt(1);
  end;
  WriteLn('Name'#9'Life'#9'XP'#9'A'#9'B'#9'Weapon'#9'Armor'#9'Max Size'#9'C'#9'D'#9'Ability');
  repeat
    Read(InputHandle, Monster);
    Write(Monster.displayName);
    Write(#9);
    Write(Monster.life);
    Write(#9);
    Write(Monster.xp);
    Write(#9);
    Write(Monster.a);
    Write(#9);
    Write(Monster.b);
    Write(#9);
    Write(Monster.wpn);
    Write(#9);
    Write(Monster.arm);
    Write(#9);
    Write(Monster.maxSize);
    Write(#9);
    Write(Monster.c);
    Write(#9);
    Write(Monster.d);
    Write(#9);
    WriteLn(Monster.ability);
  until Eof(InputHandle);
  Close(InputHandle);
end.
