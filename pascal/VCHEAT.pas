{ For most applications, consider using the Superior race cheat }
{ See https://vampyr-talisman-of-invocation.fandom.com/wiki/Save_File_Format#.22.22.22Superior.22.22.22 }
program vcheat;
const
    FileName = 'PLAYER.SAV';
type
    RaceEnum = (Human, Dwarf, Elf, Corintir, Victor, Brian);
    WeaponsEnum = (
        Hands,
        Dagger,  Staff,  Mace,  MorningStar,  Axe,
            LongSword,  TwoHSword,  LongBow,  Sling,  Club,
        Dagger1, Staff1, Mace1, MorningStar1, Axe1,
            LongSword1, TwoHSword1, LongBow1, Sling1, Club1,
        Dagger2, Staff2, Mace2, MorningStar2, Axe2,
            LongSword2, TwoHSword2, LongBow2, Sling2, Club2,
        Dagger3, Staff3, Mace3, MorningStar3, Axe3,
            LongSword3, TwoHSword3, LongBow3, Sling3, Club3,
        Slime, Bite, BigBite, GiantBite, Fist, BigFist, GiantFist, Claws,
            BigClaws, GiantClaws, VampireTouch, VampyrTouch, BigBroom);
    ArmorEnum = (Nude,
        Cloth, Padded, Leather, Studded, RingMail, ScaleMail,
            ChainMail, SplintMail, PlateMail, FullPlate,
        Cloth1, Padded1, Leather1, Studded1, RingMail1, ScaleMail1,
            ChainMail1, SplintMail1, PlateMail1, FullPlate1,
        Cloth2, Padded2, Leather2, Studded2, RingMail2, ScaleMail2,
            ChainMail2, SplintMail2, PlateMail2, FullPlate2,
        Cloth3, Padded3, Leather3, Studded3, RingMail3, ScaleMail3,
            ChainMail3, SplintMail3, PlateMail3, FullPlate3,
        Bones, ThickSkin, Transparency, Fur, ThickFur, Scales,
            MagicRobe, HardBark, SlimeCoating);
    PlayerData = record
        name       : string[10]; { Name }
        race       : RaceEnum; { Race }
        level      : 1..15; { Level }
        hpMax      : integer; { HP }
        hpNow      : integer;
        gold       : integer; { Gold }
        xp         : longint; { Experience }
        mpMax      : byte; { MP }
        mpNow      : byte;
        phyStr     : 1..20; { Stats }
        menStr     : 1..20;
        dex        : 1..20;
        con        : 1..20;
        cha        : 1..20;
        luc        : 1..20;
        fAttBase   : 1..100; { Unbuffed Skills }
        fDefBase   : 1..100;
        mOffBase   : 1..100;
        mDefBase   : 1..100;
        fAtt       : 1..100; { Buffable Skills }
        fDef       : 1..100;
        mOff       : 1..100;
        mDef       : 1..100;
        mMsc       : 1..100; { Rest of Skills }
        lockPick   : 1..100;
        climbing   : 1..100;
        stealing   : 1..100;
        perception : 1..100;
        wpn        : WeaponsEnum; { Held Weapon }
        arm        : ArmorEnum; { Worn Armor }
        msn1Flag   : boolean; { Mission progress trackers }
        msn2Flag   : boolean;
        msn3Flag   : boolean;
        msn4Flag   : boolean;
        msn5Flag   : boolean;
        msn6Flag   : boolean;
        msn1Done   : boolean; { Mission completion trackers }
        msn2Done   : boolean;
        msn3Done   : boolean;
        msn4Done   : boolean;
        msn5Done   : boolean;
        blueRose   : boolean; { Other flags }
        dalagash   : boolean;
        unknown    : boolean; { UNKNOWN! }
        rustArmor  : boolean;
        x          : byte; { Overworld Position }
        y          : byte;
        buff       : byte; { Current spell }
        turns      : byte; { Spell turn counter }
        inv        : array[1..5] of WeaponsEnum; { Weapons in inventory }
        wpnDur     : shortint; { Durability of held weapon }
        invDur     : array[1..5] of shortint; { Durability of inventory weapons }
        armDur     : shortint; { Durability of worn armor }
    end;
var
    Player : PlayerData;
    PlayerFile : file of PlayerData; { Indicate the structure of the file to load }
begin
    Assign(PlayerFile, FileName); { Say PlayerFile should open PLAYER.SAV }
    Reset(PlayerFile); { Open the file }
    Read(PlayerFile, Player); { Do the thing! }
    Player.name := 'BIG CHEATS'; { Change player data }
    Player.race := Brian;
    Player.level := 15;
    Player.hpNow := $7FFF;
    Player.hpMax := $7FFF;
    Player.mpNow := $FF;
    Player.mpMax := $FF;
    Player.gold := $6FFF; { Not max to avoid overflow }
    Player.wpn := TwoHSword3;
    Player.arm := FullPlate3;
    Player.wpnDur := $7F;
    Player.armDur := $7F;
    Player.phyStr := 20;
    Player.menStr := 20;
    Player.dex := 20;
    Player.con := 20;
    Player.cha := 20;
    Player.luc := 20;
    Player.fAttBase := 100;
    Player.fDefBase := 100;
    Player.mOffBase := 100;
    Player.mDefBase := 100;
    Player.fAtt := 100;
    Player.fDef := 100;
    Player.mOff := 100;
    Player.mDef := 100;
    Player.mMsc := 100;
    Player.lockPick := 100;
    Player.climbing := 100;
    Player.stealing := 100;
    Player.perception := 100;
    Rewrite(PlayerFile); { Go to RW mode }
    Write(PlayerFile, Player); { Write modified data }
    Close(PlayerFile); { Done with file, close to clean up }
end.