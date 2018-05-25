object Form_Chgpasswd: TForm_Chgpasswd
  Left = 197
  Top = 263
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Change Password'
  ClientHeight = 201
  ClientWidth = 342
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
  object Label_Oldpasswd: TLabel
    Left = 11
    Top = 16
    Width = 96
    Height = 16
    Caption = '       Old  Passwd'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label_Newpasswd: TLabel
    Left = 12
    Top = 69
    Width = 96
    Height = 16
    Caption = '      New Passwd'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label_Confpasswd: TLabel
    Left = 12
    Top = 117
    Width = 96
    Height = 16
    Caption = 'Confirm Passwd'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 120
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
  object Edit_Oldpasswd: TEdit
    Left = 120
    Top = 11
    Width = 209
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
    Text = 'Edit_Oldpasswd'
    OnKeyPress = Edit_OldpasswdKeyPress
  end
  object Edit_Newpasswd: TEdit
    Left = 120
    Top = 64
    Width = 209
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 1
    Text = 'Edit1'
    OnKeyPress = Edit_NewpasswdKeyPress
  end
  object Edit_Confpasswd: TEdit
    Left = 120
    Top = 112
    Width = 209
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 2
    Text = 'Edit1'
    OnKeyPress = Edit_ConfpasswdKeyPress
  end
  object btnCancel: TButton
    Left = 24
    Top = 160
    Width = 81
    Height = 33
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 248
    Top = 160
    Width = 81
    Height = 33
    Caption = 'OK'
    TabOrder = 3
    OnClick = btnOKClick
  end
end
