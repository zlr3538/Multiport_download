object dlgSetBeginComPort: TdlgSetBeginComPort
  Left = 384
  Top = 189
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'SetBeginComPort'
  ClientHeight = 52
  ClientWidth = 277
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object laSetBeginComPort: TLabel
    Left = 24
    Top = 24
    Width = 82
    Height = 13
    Caption = 'Begin COM Port :'
  end
  object ed_begin_com_port: TEdit
    Left = 112
    Top = 19
    Width = 65
    Height = 21
    MaxLength = 3
    TabOrder = 0
  end
  object cbBCPApply: TButton
    Left = 193
    Top = 17
    Width = 65
    Height = 25
    Caption = 'Apply'
    Default = True
    TabOrder = 1
    OnClick = cbBCPApplyClick
  end
  object ButtonCancel: TButton
    Left = 192
    Top = 80
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
  end
end
