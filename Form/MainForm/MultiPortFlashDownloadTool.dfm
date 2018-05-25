object MainForm: TMainForm
  Left = 617
  Top = 124
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Multiport Download Tool'
  ClientHeight = 554
  ClientWidth = 869
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  Visible = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object COM1Percentage: TLabel
    Left = 176
    Top = 190
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM2Percentage: TLabel
    Tag = 1
    Left = 176
    Top = 211
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM3Percentage: TLabel
    Tag = 2
    Left = 176
    Top = 232
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM4Percentage: TLabel
    Tag = 3
    Left = 176
    Top = 254
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM5Percentage: TLabel
    Tag = 4
    Left = 176
    Top = 275
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM6Percentage: TLabel
    Tag = 5
    Left = 176
    Top = 297
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM7Percentage: TLabel
    Tag = 6
    Left = 176
    Top = 318
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM8Percentage: TLabel
    Tag = 7
    Left = 176
    Top = 340
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lblCOM1Time: TLabel
    Left = 399
    Top = 192
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM2Time: TLabel
    Tag = 1
    Left = 399
    Top = 211
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM3Time: TLabel
    Tag = 2
    Left = 399
    Top = 232
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM4Time: TLabel
    Tag = 3
    Left = 399
    Top = 254
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM5Time: TLabel
    Tag = 4
    Left = 399
    Top = 275
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM6Time: TLabel
    Tag = 5
    Left = 399
    Top = 297
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM7Time: TLabel
    Tag = 6
    Left = 399
    Top = 318
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM8Time: TLabel
    Tag = 7
    Left = 399
    Top = 340
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object Label1: TLabel
    Left = 11
    Top = 6
    Width = 60
    Height = 13
    Caption = 'DA file name'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object pbCOM1: TCGauge
    Left = 251
    Top = 190
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
  end
  object pbCOM2: TCGauge
    Tag = 1
    Left = 251
    Top = 211
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM3: TCGauge
    Tag = 2
    Left = 251
    Top = 232
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM4: TCGauge
    Tag = 3
    Left = 251
    Top = 254
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM5: TCGauge
    Tag = 4
    Left = 251
    Top = 275
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM6: TCGauge
    Tag = 5
    Left = 251
    Top = 297
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM7: TCGauge
    Tag = 6
    Left = 251
    Top = 318
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM8: TCGauge
    Tag = 7
    Left = 251
    Top = 340
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object shpCOM1: TShape
    Left = 154
    Top = 190
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM2: TShape
    Tag = 1
    Left = 154
    Top = 211
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM4: TShape
    Tag = 3
    Left = 154
    Top = 254
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM5: TShape
    Tag = 4
    Left = 154
    Top = 275
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM6: TShape
    Tag = 5
    Left = 154
    Top = 297
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM7: TShape
    Tag = 6
    Left = 154
    Top = 318
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM8: TShape
    Tag = 7
    Left = 154
    Top = 340
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM3: TShape
    Tag = 2
    Left = 154
    Top = 232
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM9: TShape
    Tag = 8
    Left = 154
    Top = 361
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM10: TShape
    Tag = 9
    Left = 154
    Top = 383
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM11: TShape
    Tag = 10
    Left = 154
    Top = 404
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM12: TShape
    Tag = 11
    Left = 154
    Top = 426
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM13: TShape
    Tag = 12
    Left = 154
    Top = 447
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM14: TShape
    Tag = 13
    Left = 154
    Top = 469
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM15: TShape
    Tag = 14
    Left = 154
    Top = 490
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object shpCOM16: TShape
    Tag = 15
    Left = 154
    Top = 512
    Width = 17
    Height = 17
    Brush.Color = clGreen
    Shape = stCircle
  end
  object COM9Percentage: TLabel
    Tag = 8
    Left = 176
    Top = 361
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM10Percentage: TLabel
    Tag = 9
    Left = 176
    Top = 383
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM11Percentage: TLabel
    Tag = 10
    Left = 176
    Top = 404
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM12Percentage: TLabel
    Tag = 11
    Left = 176
    Top = 426
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM13Percentage: TLabel
    Tag = 12
    Left = 176
    Top = 447
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM14Percentage: TLabel
    Tag = 13
    Left = 176
    Top = 469
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM15Percentage: TLabel
    Tag = 14
    Left = 176
    Top = 490
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object COM16Percentage: TLabel
    Tag = 15
    Left = 176
    Top = 512
    Width = 73
    Height = 12
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object pbCOM9: TCGauge
    Tag = 8
    Left = 251
    Top = 361
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM10: TCGauge
    Tag = 9
    Left = 251
    Top = 383
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM11: TCGauge
    Tag = 10
    Left = 251
    Top = 404
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM12: TCGauge
    Tag = 11
    Left = 251
    Top = 426
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM13: TCGauge
    Tag = 12
    Left = 251
    Top = 447
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM14: TCGauge
    Tag = 13
    Left = 251
    Top = 469
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM15: TCGauge
    Tag = 14
    Left = 251
    Top = 490
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object pbCOM16: TCGauge
    Tag = 15
    Left = 251
    Top = 512
    Width = 129
    Height = 17
    Color = clWhite
    ForeColor = clWhite
    ParentColor = False
  end
  object lblCOM9Time: TLabel
    Tag = 8
    Left = 399
    Top = 361
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM10Time: TLabel
    Tag = 9
    Left = 399
    Top = 383
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM11Time: TLabel
    Tag = 10
    Left = 399
    Top = 404
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM12Time: TLabel
    Tag = 11
    Left = 399
    Top = 426
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM13Time: TLabel
    Tag = 12
    Left = 399
    Top = 447
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM14Time: TLabel
    Tag = 13
    Left = 399
    Top = 469
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM15Time: TLabel
    Tag = 14
    Left = 399
    Top = 490
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object lblCOM16Time: TLabel
    Tag = 15
    Left = 399
    Top = 512
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0 sec'
  end
  object Label2: TLabel
    Left = 11
    Top = 30
    Width = 84
    Height = 13
    Caption = 'Authentication file'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object m_lblBaudRate: TLabel
    Left = 608
    Top = 248
    Width = 46
    Height = 13
    Caption = 'Baud rate'
  end
  object Label3: TLabel
    Left = 11
    Top = 54
    Width = 58
    Height = 13
    Caption = 'RootCert file'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 11
    Top = 77
    Width = 66
    Height = 13
    Caption = 'Certificate File'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object btnCOM1Start: TButton
    Left = 434
    Top = 190
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 34
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM2Start: TButton
    Tag = 1
    Left = 434
    Top = 211
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 35
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM3Start: TButton
    Tag = 2
    Left = 434
    Top = 232
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 36
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM4Start: TButton
    Tag = 3
    Left = 434
    Top = 254
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 37
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM5Start: TButton
    Tag = 4
    Left = 434
    Top = 275
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 38
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM6Start: TButton
    Tag = 5
    Left = 434
    Top = 297
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 39
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM7Start: TButton
    Tag = 6
    Left = 434
    Top = 318
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 40
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM8Start: TButton
    Tag = 7
    Left = 434
    Top = 340
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 41
    OnClick = btnSeperateDownloadClick
  end
  object btnStartAll: TButton
    Left = 613
    Top = 501
    Width = 65
    Height = 29
    Caption = 'Start All'
    TabOrder = 66
    OnClick = btnStartAllClick
  end
  object cbAutoPolling1: TCheckBox
    Left = 64
    Top = 190
    Width = 89
    Height = 17
    Caption = 'Auto polling1'
    TabOrder = 18
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling2: TCheckBox
    Tag = 1
    Left = 64
    Top = 211
    Width = 89
    Height = 17
    Caption = 'Auto polling2'
    TabOrder = 19
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling3: TCheckBox
    Tag = 2
    Left = 64
    Top = 232
    Width = 89
    Height = 17
    Caption = 'Auto polling3'
    TabOrder = 20
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling4: TCheckBox
    Tag = 3
    Left = 64
    Top = 254
    Width = 89
    Height = 17
    Caption = 'Auto polling4'
    TabOrder = 21
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling5: TCheckBox
    Tag = 4
    Left = 64
    Top = 275
    Width = 89
    Height = 17
    Caption = 'Auto polling5'
    TabOrder = 22
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling6: TCheckBox
    Tag = 5
    Left = 64
    Top = 297
    Width = 89
    Height = 17
    Caption = 'Auto polling6'
    TabOrder = 23
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling7: TCheckBox
    Tag = 6
    Left = 64
    Top = 318
    Width = 89
    Height = 17
    Caption = 'Auto polling7'
    TabOrder = 24
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling8: TCheckBox
    Tag = 7
    Left = 64
    Top = 340
    Width = 89
    Height = 17
    Caption = 'Auto polling8'
    TabOrder = 25
    OnClick = cbAutoPollingClick
  end
  object cbCOM1: TCheckBox
    Left = 8
    Top = 192
    Width = 57
    Height = 17
    Caption = 'COM1'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = cbCOMClick
  end
  object cbCOM2: TCheckBox
    Tag = 1
    Left = 8
    Top = 213
    Width = 57
    Height = 17
    Caption = 'COM2'
    TabOrder = 3
    OnClick = cbCOMClick
  end
  object cbCOM3: TCheckBox
    Tag = 2
    Left = 8
    Top = 234
    Width = 57
    Height = 17
    Caption = 'COM3'
    TabOrder = 4
    OnClick = cbCOMClick
  end
  object cbCOM4: TCheckBox
    Tag = 3
    Left = 8
    Top = 256
    Width = 57
    Height = 17
    Caption = 'COM4'
    TabOrder = 5
    OnClick = cbCOMClick
  end
  object cbCOM5: TCheckBox
    Tag = 4
    Left = 8
    Top = 277
    Width = 57
    Height = 17
    Caption = 'COM5'
    TabOrder = 6
    OnClick = cbCOMClick
  end
  object cbCOM6: TCheckBox
    Tag = 5
    Left = 8
    Top = 298
    Width = 57
    Height = 17
    Caption = 'COM6'
    TabOrder = 7
    OnClick = cbCOMClick
  end
  object cbCOM7: TCheckBox
    Tag = 6
    Left = 8
    Top = 320
    Width = 57
    Height = 17
    Caption = 'COM7'
    TabOrder = 8
    OnClick = cbCOMClick
  end
  object cbCOM8: TCheckBox
    Tag = 7
    Left = 8
    Top = 341
    Width = 57
    Height = 17
    Caption = 'COM8'
    TabOrder = 9
    OnClick = cbCOMClick
  end
  object btnCOM1Stop: TButton
    Left = 474
    Top = 190
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 50
    OnClick = btnSeperateStopClick
  end
  object btnCOM2Stop: TButton
    Tag = 1
    Left = 474
    Top = 211
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 51
    OnClick = btnSeperateStopClick
  end
  object btnCOM3Stop: TButton
    Tag = 2
    Left = 474
    Top = 232
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 52
    OnClick = btnSeperateStopClick
  end
  object btnCOM4Stop: TButton
    Tag = 3
    Left = 474
    Top = 254
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 53
    OnClick = btnSeperateStopClick
  end
  object btnCOM5Stop: TButton
    Tag = 4
    Left = 474
    Top = 275
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 54
    OnClick = btnSeperateStopClick
  end
  object btnCOM6Stop: TButton
    Tag = 5
    Left = 474
    Top = 297
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 55
    OnClick = btnSeperateStopClick
  end
  object btnCOM7Stop: TButton
    Tag = 6
    Left = 474
    Top = 318
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 56
    OnClick = btnSeperateStopClick
  end
  object btnCOM8Stop: TButton
    Tag = 7
    Left = 474
    Top = 340
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 57
    OnClick = btnSeperateStopClick
  end
  object btnStopAll: TButton
    Left = 697
    Top = 501
    Width = 65
    Height = 30
    Caption = 'Stop All'
    TabOrder = 67
    OnClick = btnStopAllClick
  end
  object cbCOM9: TCheckBox
    Tag = 8
    Left = 8
    Top = 362
    Width = 57
    Height = 17
    Caption = 'COM9'
    TabOrder = 10
    OnClick = cbCOMClick
  end
  object cbCOM10: TCheckBox
    Tag = 9
    Left = 8
    Top = 384
    Width = 57
    Height = 17
    Caption = 'COM10'
    TabOrder = 11
    OnClick = cbCOMClick
  end
  object cbCOM11: TCheckBox
    Tag = 10
    Left = 8
    Top = 405
    Width = 57
    Height = 17
    Caption = 'COM11'
    TabOrder = 12
    OnClick = cbCOMClick
  end
  object cbCOM12: TCheckBox
    Tag = 11
    Left = 8
    Top = 426
    Width = 57
    Height = 17
    Caption = 'COM12'
    TabOrder = 13
    OnClick = cbCOMClick
  end
  object cbCOM13: TCheckBox
    Tag = 12
    Left = 8
    Top = 448
    Width = 57
    Height = 17
    Caption = 'COM13'
    TabOrder = 14
    OnClick = cbCOMClick
  end
  object cbCOM14: TCheckBox
    Tag = 13
    Left = 8
    Top = 469
    Width = 57
    Height = 17
    Caption = 'COM14'
    TabOrder = 15
    OnClick = cbCOMClick
  end
  object cbCOM15: TCheckBox
    Tag = 14
    Left = 8
    Top = 490
    Width = 57
    Height = 17
    Caption = 'COM15'
    TabOrder = 16
    OnClick = cbCOMClick
  end
  object cbCOM16: TCheckBox
    Tag = 15
    Left = 8
    Top = 512
    Width = 57
    Height = 17
    Caption = 'COM16'
    TabOrder = 17
    OnClick = cbCOMClick
  end
  object cbAutoPolling9: TCheckBox
    Tag = 8
    Left = 64
    Top = 361
    Width = 89
    Height = 17
    Caption = 'Auto polling9'
    TabOrder = 26
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling10: TCheckBox
    Tag = 9
    Left = 64
    Top = 383
    Width = 89
    Height = 17
    Caption = 'Auto polling10'
    TabOrder = 27
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling11: TCheckBox
    Tag = 10
    Left = 64
    Top = 404
    Width = 89
    Height = 17
    Caption = 'Auto polling11'
    TabOrder = 28
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling12: TCheckBox
    Tag = 11
    Left = 64
    Top = 426
    Width = 89
    Height = 17
    Caption = 'Auto polling12'
    TabOrder = 29
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling13: TCheckBox
    Tag = 12
    Left = 64
    Top = 447
    Width = 89
    Height = 17
    Caption = 'Auto polling13'
    TabOrder = 30
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling14: TCheckBox
    Tag = 13
    Left = 64
    Top = 469
    Width = 89
    Height = 17
    Caption = 'Auto polling14'
    TabOrder = 31
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling15: TCheckBox
    Tag = 14
    Left = 64
    Top = 490
    Width = 89
    Height = 17
    Caption = 'Auto polling15'
    TabOrder = 32
    OnClick = cbAutoPollingClick
  end
  object cbAutoPolling16: TCheckBox
    Tag = 15
    Left = 64
    Top = 512
    Width = 89
    Height = 17
    Caption = 'Auto polling16'
    TabOrder = 33
    OnClick = cbAutoPollingClick
  end
  object btnCOM9Start: TButton
    Tag = 8
    Left = 434
    Top = 361
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 42
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM10Start: TButton
    Tag = 9
    Left = 434
    Top = 383
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 43
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM11Start: TButton
    Tag = 10
    Left = 434
    Top = 404
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 44
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM12Start: TButton
    Tag = 11
    Left = 434
    Top = 426
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 45
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM13Start: TButton
    Tag = 12
    Left = 434
    Top = 447
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 46
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM14Start: TButton
    Tag = 13
    Left = 434
    Top = 469
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 47
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM15Start: TButton
    Tag = 14
    Left = 434
    Top = 490
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 48
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM16Start: TButton
    Tag = 15
    Left = 434
    Top = 512
    Width = 40
    Height = 17
    Caption = 'Start'
    TabOrder = 49
    OnClick = btnSeperateDownloadClick
  end
  object btnCOM9Stop: TButton
    Tag = 8
    Left = 474
    Top = 361
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 58
    OnClick = btnSeperateStopClick
  end
  object btnCOM10Stop: TButton
    Tag = 9
    Left = 474
    Top = 383
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 59
    OnClick = btnSeperateStopClick
  end
  object btnCOM11Stop: TButton
    Tag = 10
    Left = 474
    Top = 404
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 60
    OnClick = btnSeperateStopClick
  end
  object btnCOM12Stop: TButton
    Tag = 11
    Left = 474
    Top = 426
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 61
    OnClick = btnSeperateStopClick
  end
  object btnCOM13Stop: TButton
    Tag = 12
    Left = 474
    Top = 447
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 62
    OnClick = btnSeperateStopClick
  end
  object btnCOM14Stop: TButton
    Tag = 13
    Left = 474
    Top = 469
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 63
    OnClick = btnSeperateStopClick
  end
  object btnCOM15Stop: TButton
    Tag = 14
    Left = 474
    Top = 490
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 64
    OnClick = btnSeperateStopClick
  end
  object btnCOM16Stop: TButton
    Tag = 15
    Left = 474
    Top = 512
    Width = 40
    Height = 17
    Caption = 'Stop'
    TabOrder = 65
    OnClick = btnSeperateStopClick
  end
  object m_stBkStatus0: TStaticText
    Left = 518
    Top = 190
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 68
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus1: TStaticText
    Tag = 1
    Left = 518
    Top = 211
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 69
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus2: TStaticText
    Tag = 2
    Left = 518
    Top = 232
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 70
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus3: TStaticText
    Tag = 3
    Left = 518
    Top = 254
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 71
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus4: TStaticText
    Tag = 4
    Left = 518
    Top = 275
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 72
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus5: TStaticText
    Tag = 5
    Left = 518
    Top = 297
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 73
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus6: TStaticText
    Tag = 6
    Left = 518
    Top = 318
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 74
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus7: TStaticText
    Tag = 7
    Left = 518
    Top = 340
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 75
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus8: TStaticText
    Tag = 8
    Left = 518
    Top = 361
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 76
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus9: TStaticText
    Tag = 9
    Left = 518
    Top = 383
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 77
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus10: TStaticText
    Tag = 10
    Left = 518
    Top = 404
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 78
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus11: TStaticText
    Tag = 11
    Left = 518
    Top = 426
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 79
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus12: TStaticText
    Tag = 12
    Left = 518
    Top = 447
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 80
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus13: TStaticText
    Tag = 13
    Left = 518
    Top = 469
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 81
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus14: TStaticText
    Tag = 14
    Left = 518
    Top = 490
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 82
    OnDblClick = m_stBkStatusDbClick
  end
  object m_stBkStatus15: TStaticText
    Tag = 15
    Left = 518
    Top = 512
    Width = 65
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Color = clMoneyGreen
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 83
    OnDblClick = m_stBkStatusDbClick
  end
  object cbSelAllCOM: TCheckBox
    Left = 8
    Top = 168
    Width = 57
    Height = 17
    Caption = 'Sel All'
    TabOrder = 0
    OnClick = cbSelAllCOMClick
  end
  object cbSelAllAutoPolling: TCheckBox
    Left = 64
    Top = 168
    Width = 57
    Height = 17
    Caption = 'Sel All'
    TabOrder = 1
    OnClick = cbSelAllAutoPollingClick
  end
  object stDAFileName: TEdit
    Left = 100
    Top = 4
    Width = 665
    Height = 21
    Color = clSkyBlue
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 84
  end
  object stAuthFile: TEdit
    Left = 100
    Top = 27
    Width = 665
    Height = 21
    Color = clSkyBlue
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 85
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 107
    Width = 761
    Height = 49
    Caption = 'Scatter/Config Files Folder Path'
    TabOrder = 86
    object btnReloadScatterFile: TButton
      Left = 704
      Top = 19
      Width = 49
      Height = 18
      Caption = 'Reload'
      TabOrder = 1
      OnClick = btnReloadScatterFileClick
    end
    object stScatterFile: TEdit
      Left = 88
      Top = 16
      Width = 601
      Height = 21
      Color = clSkyBlue
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 2
    end
    object ScatterFileButton3: TButton
      Tag = 2
      Left = 16
      Top = 128
      Width = 73
      Height = 17
      Caption = 'Scatter File 3'
      TabOrder = 4
      Visible = False
      OnClick = ScatterFileButtonClick
    end
    object SctterFileButton4: TButton
      Tag = 3
      Left = 16
      Top = 152
      Width = 73
      Height = 17
      Caption = 'Scatter File 4'
      TabOrder = 5
      Visible = False
      OnClick = ScatterFileButtonClick
    end
    object stScatterFile2: TEdit
      Left = 96
      Top = 104
      Width = 609
      Height = 21
      Color = clSkyBlue
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 6
      Visible = False
    end
    object stScatterFile3: TEdit
      Left = 96
      Top = 128
      Width = 609
      Height = 21
      Color = clSkyBlue
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 7
      Visible = False
    end
    object stScatterFile4: TEdit
      Left = 96
      Top = 152
      Width = 609
      Height = 21
      Color = clSkyBlue
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 8
      Visible = False
    end
    object btDeleteScatterFile2: TButton
      Tag = 1
      Left = 712
      Top = 104
      Width = 49
      Height = 17
      Caption = 'Delete'
      TabOrder = 9
      Visible = False
      OnClick = btnReloadScatterFileClick
    end
    object btDeleteScatterFile3: TButton
      Tag = 2
      Left = 712
      Top = 128
      Width = 49
      Height = 17
      Caption = 'Delete'
      TabOrder = 10
      Visible = False
      OnClick = btnReloadScatterFileClick
    end
    object btDeleteScatterFile4: TButton
      Tag = 3
      Left = 712
      Top = 152
      Width = 49
      Height = 17
      Caption = 'Delete'
      TabOrder = 11
      Visible = False
      OnClick = btnReloadScatterFileClick
    end
    object ScatterFileButton1: TButton
      Left = 6
      Top = 16
      Width = 73
      Height = 24
      Caption = 'Image Folder'
      TabOrder = 0
      OnClick = ScatterFileButtonClick
    end
    object ScatterFileButton2: TButton
      Tag = 1
      Left = 16
      Top = 104
      Width = 73
      Height = 17
      Caption = 'Scatter File 2'
      TabOrder = 3
      Visible = False
      OnClick = ScatterFileButtonClick
    end
  end
  object ActionPage: TPageControl
    Left = 597
    Top = 277
    Width = 172
    Height = 217
    ActivePage = DownloadAction
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabIndex = 0
    TabOrder = 87
    object DownloadAction: TTabSheet
      Caption = 'Download/Format'
      object Label4: TLabel
        Left = 104
        Top = 0
        Width = 46
        Height = 13
        Caption = 'Operation'
      end
      object cbType: TComboBox
        Left = 6
        Top = 20
        Width = 153
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbTypeChange
      end
      object gbFormatFATRange: TGroupBox
        Left = 4
        Top = 50
        Width = 153
        Height = 137
        Caption = '  Format FAT Options  '
        TabOrder = 1
        object rbAuto: TRadioButton
          Left = 8
          Top = 16
          Width = 133
          Height = 17
          Caption = 'Auto'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object rbManual: TRadioButton
          Left = 8
          Top = 33
          Width = 80
          Height = 17
          Caption = 'Manual'
          TabOrder = 2
          OnClick = rbManualClick
        end
        object rbResetToFactory: TRadioButton
          Left = 8
          Top = 104
          Width = 137
          Height = 25
          Hint = '(for after W05.48)'
          Caption = 'Reset to factory default '
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
        end
        object GroupBox1: TGroupBox
          Left = 24
          Top = 49
          Width = 105
          Height = 57
          Caption = 'Flash  Type'
          TabOrder = 0
          object rbNAND: TRadioButton
            Left = 8
            Top = 16
            Width = 81
            Height = 17
            Caption = 'NAND/NFB'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = rbNANDClick
            OnMouseUp = rbNANDMouseUp
          end
          object rbNOR: TRadioButton
            Left = 8
            Top = 32
            Width = 57
            Height = 17
            Caption = 'NOR'
            TabOrder = 1
            OnClick = rbNORClick
            OnMouseUp = rbNORMouseUp
          end
        end
      end
      object BootCertOptions: TGroupBox
        Left = 4
        Top = 67
        Width = 153
        Height = 97
        Caption = 'Boot Cert Option'
        TabOrder = 2
        Visible = False
        object Btn_Select_RootCert_File: TButton
          Left = 8
          Top = 22
          Width = 129
          Height = 25
          Caption = 'Select BootCert_File...'
          TabOrder = 0
          OnClick = Btn_Select_RootCert_FileClick
        end
      end
    end
    object eFuse: TTabSheet
      Caption = 'eFuse'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ImageIndex = 1
      ParentFont = False
      TabVisible = False
      object eFuseOperation: TGroupBox
        Left = 4
        Top = 7
        Width = 165
        Height = 186
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object btnSelectEFuseSettingFile: TButton
          Left = 80
          Top = 21
          Width = 81
          Height = 24
          Caption = 'SettingFile...'
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = btnSelectEFuseSettingFileClick
        end
        object btnSelectEFuseLockFile: TButton
          Left = 80
          Top = 59
          Width = 81
          Height = 24
          Caption = ' Lock File...'
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = btnSelectEFuseLockFileClick
        end
        object btnEFuseParameterView: TButton
          Left = 32
          Top = 144
          Width = 99
          Height = 32
          Caption = 'View Setting'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          OnClick = btnEFuseParameterViewClick
        end
        object EFuseWriteCheckBox: TCheckBox
          Left = 10
          Top = 24
          Width = 57
          Height = 17
          Caption = 'Write'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = EFuseWriteCheckBoxClick
        end
        object EFuseLockCheckBox: TCheckBox
          Left = 9
          Top = 63
          Width = 64
          Height = 17
          Caption = 'Lock'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = EFuseLockCheckBoxClick
        end
        object EFuseReadCheckBox: TCheckBox
          Left = 8
          Top = 104
          Width = 97
          Height = 17
          Caption = 'Read'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = EFuseReadCheckBoxClick
        end
      end
    end
  end
  object sbMPDT: TStatusBar
    Left = 0
    Top = 534
    Width = 869
    Height = 20
    Panels = <
      item
        Width = 500
      end>
    SimplePanel = False
  end
  object m_Gb_ComPortType: TGroupBox
    Left = 606
    Top = 155
    Width = 164
    Height = 81
    Caption = 'COM Port'
    TabOrder = 89
    object m_rbUART: TRadioButton
      Left = 8
      Top = 16
      Width = 129
      Height = 17
      Hint = 'UART Download'
      Caption = 'UART'
      Checked = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      TabStop = True
      OnClick = m_rbUARTClick
    end
    object m_rbUSB: TRadioButton
      Left = 8
      Top = 33
      Width = 137
      Height = 22
      Hint = 'USB Download'
      Caption = 'USB'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = m_rbUSBClick
    end
    object m_rbUART_USB: TRadioButton
      Left = 8
      Top = 56
      Width = 138
      Height = 14
      Hint = 'One Station Download'
      Caption = 'UART + USB'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = m_rbUART_USB_Click
    end
  end
  object cbBaudrate: TComboBox
    Left = 667
    Top = 243
    Width = 89
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 90
    Text = '115200'
    OnChange = cbBaudrateChange
    Items.Strings = (
      '115200'
      '230400'
      '460800'
      '921600')
  end
  object RootCert_File_DisplayEdit: TEdit
    Left = 100
    Top = 50
    Width = 665
    Height = 21
    Color = clSkyBlue
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 91
  end
  object Certificate_File_DisplayEdit: TEdit
    Left = 100
    Top = 74
    Width = 665
    Height = 21
    Color = clSkyBlue
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 92
  end
  object TimerCOM1: TTimer
    OnTimer = TimerCOMTimer
    Left = 797
    Top = 24
  end
  object dlgOpenDA: TOpenDialog
    DefaultExt = '*.bin'
    Filter = 'Bin File (*.bin)|*.bin|All File (*.*)|*.*'
    Title = 'Open'
    Left = 797
    Top = 288
  end
  object MainMenu1: TMainMenu
    Left = 797
    Top = 64
    object miFile: TMenuItem
      Caption = '&File'
      ShortCut = 16454
      object OpenDownloadAgentFile1: TMenuItem
        Caption = 'Open Download Agent File'
        OnClick = OpenDownloadAgentFile1Click
      end
      object miOpenAuthFile: TMenuItem
        Caption = 'Open Authentication File'
        OnClick = miOpenAuthFileClick
      end
      object OpenMemoryVerificationListFile1: TMenuItem
        Caption = 'Open Memory Verification List Excel File'
        Visible = False
        OnClick = OpenMemoryVerificationListFile1Click
      end
      object Show_scatter_and_load: TMenuItem
        Caption = 'Scatter and Load'
        OnClick = Show_scatter_and_loadClick
      end
      object OpenRootCertFile: TMenuItem
        Caption = 'Open Root Cert File'
        OnClick = OpenRootCertFileClick
      end
      object OpenCertificateFile: TMenuItem
        Caption = 'Open Certificate File'
        OnClick = OpenCertificateFileClick
      end
    end
    object miFactoryDatabase: TMenuItem
      Caption = 'Factory &Database'
      ShortCut = 16452
      object miSetupDataSrc: TMenuItem
        Caption = 'Setup data source file'
        OnClick = miSetupDataSrcClick
      end
      object miEnableFDLog: TMenuItem
        Caption = 'Enable factory database logging'
        OnClick = miEnableFDLogClick
      end
      object ShowFactoryDatabaseFile: TMenuItem
        Caption = 'Show Factory Database File'
        OnClick = ShowFactoryDatabaseFileClick
      end
    end
    object miOption: TMenuItem
      Caption = '&Options'
      ShortCut = 16463
      object miExternalclock: TMenuItem
        Caption = 'External clock'
        Enabled = False
        object miAutodetectExtClock: TMenuItem
          Caption = 'Auto detect'
          OnClick = miAutodetectExtClockClick
        end
        object mi13MHz: TMenuItem
          Caption = '13 MHz'
          OnClick = mi13MHzClick
        end
        object mi26MHz: TMenuItem
          Caption = '26 MHz'
          Checked = True
          OnClick = mi26MHzClick
        end
        object mi39MHz: TMenuItem
          Caption = '39 MHz'
          OnClick = mi39MHzClick
        end
        object mi52MHz: TMenuItem
          Caption = '52 MHz'
          OnClick = mi52MHzClick
        end
      end
      object miBasebandchipoption: TMenuItem
        Caption = 'Baseband chip options'
        object miCheckECOversion: TMenuItem
          Caption = 'Check ECO version'
          Checked = True
          Visible = False
          OnClick = miCheckECOversionClick
        end
        object miEnableNFICS1: TMenuItem
          Caption = 'Enable NFI CS1'
          OnClick = miEnableNFICS1Click
        end
        object miBBChipVersionCheck: TMenuItem
          Caption = 'BBChip Version Check'
          Checked = True
          OnClick = miBBChipVersionCheckClick
        end
      end
      object m_miBackupCalDataOption: TMenuItem
        Caption = 'Backup and restore calibration data options'
        object m_miDnWithoutBkAndRsCalData: TMenuItem
          Caption = 'Download/format without backup and restore calibration data'
          OnClick = m_miDnWithoutBkAndRsCalDataClick
        end
        object m_miDnWithBkAndRsCalData: TMenuItem
          Caption = 'Download/format with backup and restore calibration data'
          OnClick = m_miDnWithBkAndRsCalDataClick
        end
        object m_miDnAndRsCalDataOnly: TMenuItem
          Caption = 'Download/format and restore calibration data '
          OnClick = m_miDnAndRsCalDataOnlyClick
        end
        object m_miDnAndUlUserData: TMenuItem
          Caption = 'Download/format with upload user data'
          OnClick = m_miDnAndUlUserDataClick
        end
        object m_miRsCalDataOnly: TMenuItem
          Caption = 'Restore calibration data only'
          OnClick = m_miRsCalDataOnlyClick
        end
        object m_miUploadUserDataOnly: TMenuItem
          Caption = 'Upload User Data Only'
          OnClick = m_miUploadUserDataOnlyClick
        end
        object m_miCheckSDS: TMenuItem
          Caption = 'CheckSDS'
          OnClick = m_miCheckSDSClick
        end
      end
      object SetbeginCOMport1: TMenuItem
        Caption = 'Set begin COM port'
        OnClick = SetbeginCOMport1Click
      end
      object USBDownloadWOBattery: TMenuItem
        Caption = 'USB Download W/O Battery'
        OnClick = USBDownloadWOBatteryClick
      end
      object mi_USBDownloadReadbackDataCard: TMenuItem
        Caption = 'USB Download/Format  (Data Card)'
        OnClick = mi_USBDownloadReadbackDataCardClick
      end
      object mi_USBDownloadReadbackDualTalk: TMenuItem
        Caption = 'USB Download/Readback(External Modem)'
        OnClick = mi_USBDownloadReadbackDualTalkClick
      end
      object miEnableMMAA1: TMenuItem
        Caption = 'Enable MMAA (Multi-Load with Multi-Memory)'
        OnClick = miEnableMMAA1Click
      end
      object miUSBDLWithTwoSteps: TMenuItem
        Caption = 'USB download with two steps'
        Checked = True
        Default = True
        Visible = False
        OnClick = miUSBDLWithTwoStepsClick
      end
      object SendRootCertForcely: TMenuItem
        Caption = 'Send RootCert Forcely'
        OnClick = SendRootCertForcelyClick
      end
      object USBMetaModeAfterOneStationDownload1: TMenuItem
        Caption = 'USB Meta Mode After One Station Download'
        OnClick = USBMetaModeAfterOneStationDownload1Click
      end
      object EnableUSB11to20: TMenuItem
        Caption = 'Enable USB 1.1 to 2.0'
        OnClick = EnableUSB11to20Click
      end
      object EnableBackupNvramPartion: TMenuItem
        Caption = 'Backup Nvram Partition'
        OnClick = EnableBackupNvramPartionClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object miEnterMetaModeafterDLFMT1: TMenuItem
        Caption = 'Enter Meta Mode after DL/FMT'
        OnClick = miEnterMetaModeafterDLFMT1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object miToolSetting: TMenuItem
        Caption = 'Settings...'
        ShortCut = 118
        OnClick = miToolSettingClick
      end
      object FlashSafeMode: TMenuItem
        Caption = 'Nor/SF Flash Safe Mode'
        OnClick = FlashSafeModeClick
      end
    end
    object miDebuglog: TMenuItem
      Caption = 'Debug &Logging'
      ShortCut = 16460
      object miBromDllLog: TMenuItem
        Caption = 'Enable BROM_DLL logging'
        OnClick = miBromDllLogClick
      end
      object miClearBromDllLog: TMenuItem
        Caption = 'Clear BROM_DLL log'
        OnClick = miClearBromDllLogClick
      end
      object miMETADllLog: TMenuItem
        Caption = 'Enable META_DLL logging'
        OnClick = miMETADllLogClick
      end
      object miClearMETADllLog: TMenuItem
        Caption = 'Clear META_DLL log'
        OnClick = miClearMETADllLogClick
      end
      object miMDTLog: TMenuItem
        Caption = 'Enable  MDT logging'
        OnClick = miMDTLogClick
      end
      object miClearMDTLog: TMenuItem
        Caption = 'Clear MDT log'
        OnClick = miClearMDTLogClick
      end
      object debug_logging_separater: TMenuItem
        Caption = '-'
      end
      object ClearAllLogs: TMenuItem
        Caption = 'Clear All logs'
        ShortCut = 49219
        OnClick = ClearAllLogsClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object OpenDeviceManager1: TMenuItem
        Caption = 'Open Device Manager'
        ShortCut = 49220
        OnClick = OpenDeviceManager1Click
      end
    end
    object Identify1: TMenuItem
      Caption = 'Identify'
      object Engineer1: TMenuItem
        Caption = 'Engineer'
        object SwitchToOperator1: TMenuItem
          Caption = 'SwitchToOperator'
          OnClick = SwitchToOperator1Click
        end
        object ChangePassword1: TMenuItem
          Caption = 'ChangePassword'
          OnClick = ChangePassword1Click
        end
      end
      object Operator1: TMenuItem
        Caption = 'Operator'
        object SwitchToEngineer1: TMenuItem
          Caption = 'SwitchToEngineer'
          OnClick = SwitchToEngineer1Click
        end
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      ShortCut = 16456
      object miAbout: TMenuItem
        Caption = '&About'
        ShortCut = 16449
        OnClick = miAboutClick
      end
    end
  end
  object DataSrc: TDataSource
    Left = 797
    Top = 160
  end
  object ADOTab: TADOTable
    Connection = ADOConn
    Left = 797
    Top = 96
  end
  object ADOConn: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Multiport downlo' +
      'ad source\Multiport_DL source v2.4.1013.1\output\MTK_DATABASE.md' +
      'b;Persist Security Info=False'
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 797
    Top = 128
  end
  object dlgOpenDataSrc: TOpenDialog
    Filter = 'mdb files (*.mdb)|*.mdb'
    Left = 797
    Top = 256
  end
  object dlgOpenAuthFile: TOpenDialog
    DefaultExt = '*.auth'
    Filter = 'Authentication File (*.auth)|*.auth|All File (*.*)|*.*'
    InitialDir = '.'
    Title = 'Open AUTH File'
    Left = 798
    Top = 224
  end
  object eFuseSettingFile: TOpenDialog
    Left = 797
    Top = 328
  end
  object eFuseLockFile: TOpenDialog
    Left = 797
    Top = 360
  end
  object ActionList1: TActionList
    Left = 797
    Top = 392
    object EnableDisableeFuseWtitter: TAction
      Category = 'HotKeyAction'
      Caption = 'EnableDisableeFuseWriter'
      ShortCut = 49221
      OnExecute = EnableDisableeFuseWriter
    end
  end
  object eFuseSettingDialog: TOpenDialog
    Filter = 'IniFile(*.ini)|*.ini'
    Left = 681
    Top = 301
  end
  object eFuseLockDialog: TOpenDialog
    Filter = 'IniFile(*.ini)|*.ini'
    Left = 705
    Top = 301
  end
  object BootCert_File_OpenDialog: TOpenDialog
    Left = 704
    Top = 381
  end
  object SaveDialog1: TSaveDialog
    Left = 448
    Top = 296
  end
  object RootCertFileOpenDialog: TOpenDialog
    Left = 800
    Top = 424
  end
  object CertificateFileOpenDialog: TOpenDialog
    Left = 800
    Top = 456
  end
end
