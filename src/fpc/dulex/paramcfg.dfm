object FormParam: TFormParam
  Left = 412
  Top = 192
  BorderStyle = bsDialog
  Caption = #31995#32479#21442#25968#35774#32622
  ClientHeight = 131
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StaticText1: TStaticText
    Left = 12
    Top = 20
    Width = 64
    Height = 17
    Caption = #21069#32622#26381#21153#22120
    TabOrder = 0
  end
  object edtServer1: TEdit
    Left = 84
    Top = 20
    Width = 185
    Height = 21
    TabOrder = 1
  end
  object edtPwd: TEdit
    Left = 84
    Top = 100
    Width = 185
    Height = 21
    PasswordChar = '*'
    TabOrder = 2
  end
  object StaticText2: TStaticText
    Left = 12
    Top = 100
    Width = 52
    Height = 17
    Caption = #31649#29702#21475#20196
    TabOrder = 3
  end
  object Button1: TButton
    Left = 292
    Top = 60
    Width = 75
    Height = 25
    Caption = #30830' '#23450
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 292
    Top = 96
    Width = 75
    Height = 25
    Caption = #21462' '#28040
    TabOrder = 5
    OnClick = Button2Click
  end
  object StaticText3: TStaticText
    Left = 12
    Top = 48
    Width = 64
    Height = 17
    Caption = #20840#23616#26381#21153#22120
    TabOrder = 6
  end
  object edtServer2: TEdit
    Left = 84
    Top = 48
    Width = 185
    Height = 21
    TabOrder = 7
  end
  object StaticText4: TStaticText
    Left = 84
    Top = 76
    Width = 156
    Height = 17
    Caption = 'servant:tcp -h 127.0.0.1 -p 4501'
    Color = clRed
    ParentColor = False
    TabOrder = 8
  end
end
