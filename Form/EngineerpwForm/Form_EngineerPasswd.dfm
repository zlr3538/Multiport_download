object Form_Engineerpw: TForm_Engineerpw
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Engineer password'
  ClientHeight = 102
  ClientWidth = 319
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 20
  object Label_Passwd: TLabel
    Left = 24
    Top = 24
    Width = 60
    Height = 16
    Caption = 'Password'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label_Info: TLabel
    Left = 104
    Top = 40
    Width = 111
    Height = 13
    Caption = 'default password "000"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Edit_Passwd: TEdit
    Left = 104
    Top = 16
    Width = 201
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
    Text = 'Edit_Passwd'
    OnKeyPress = Edit_PasswdKeyPress
  end
  object btnCancel: TButton
    Left = 16
    Top = 56
    Width = 73
    Height = 33
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 224
    Top = 56
    Width = 73
    Height = 33
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOKClick
  end
end
