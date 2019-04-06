{ prints SIGN.DAT as a tab-delimited CSV }
program SignPrinter;
type
  SignData = record
    x : byte;
    y : byte;
    line1 : string[70];
    line2 : string[70];
  end;
var
  InputHandle : file of SignData;
  Sign : SignData;
begin
  if ParamCount <> 1 then
  begin
    WriteLn('Usage: sign SIGN.DAT');
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
  WriteLn('X'#9'Y'#9'Line1'#9'Line2');
  repeat
  Read(InputHandle, Sign);
    Write(Sign.x);
    Write(#9);
    Write(Sign.y);
    Write(#9);
    Write(Sign.line1);
    Write(#9);
    WriteLn(Sign.line2);
  until Eof(InputHandle);
  Close(InputHandle);
end.
