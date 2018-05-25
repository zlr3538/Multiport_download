object frmMultiLoad: TfrmMultiLoad
  Left = 217
  Top = 15
  Width = 807
  Height = 753
  Caption = '  Scatter and Load Setting'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lv1: TListView
    Left = 6
    Top = 72
    Width = 746
    Height = 73
    Checkboxes = True
    Columns = <
      item
        Caption = 'Name'
        Width = 100
      end
      item
        Caption = 'Region address'
        Width = 100
      end
      item
        Caption = 'Begin Address'
        Width = 100
      end
      item
        Caption = 'End Address'
        Width = 100
      end
      item
        Caption = 'Location'
        Width = 500
      end>
    TabOrder = 0
    ViewStyle = vsReport
    OnChange = lvChange
    OnChanging = lvChanging
    OnClick = lvClick
  end
  object lblScatFileName1: TStaticText
    Left = 88
    Top = 2
    Width = 665
    Height = 17
    AutoSize = False
    BorderStyle = sbsSunken
    Color = clSkyBlue
    ParentColor = False
    TabOrder = 1
  end
  object lv2: TListView
    Tag = 1
    Left = 6
    Top = 216
    Width = 746
    Height = 73
    Checkboxes = True
    Columns = <
      item
        Caption = 'Name'
        Width = 100
      end
      item
        Caption = 'Region address'
        Width = 100
      end
      item
        Caption = 'Begin Address'
        Width = 100
      end
      item
        Caption = 'End Address'
        Width = 100
      end
      item
        Caption = 'Location'
        Width = 500
      end>
    TabOrder = 2
    ViewStyle = vsReport
    OnChange = lvChange
    OnChanging = lvChanging
    OnClick = lvClick
  end
  object lv3: TListView
    Tag = 2
    Left = 6
    Top = 360
    Width = 746
    Height = 73
    Checkboxes = True
    Columns = <
      item
        Caption = 'Name'
        Width = 100
      end
      item
        Caption = 'Region address'
        Width = 100
      end
      item
        Caption = 'Begin Address'
        Width = 100
      end
      item
        Caption = 'End Address'
        Width = 100
      end
      item
        Caption = 'Location'
        Width = 500
      end>
    TabOrder = 3
    ViewStyle = vsReport
    OnChange = lvChange
    OnChanging = lvChanging
    OnClick = lvClick
  end
  object lv4: TListView
    Tag = 3
    Left = 6
    Top = 504
    Width = 746
    Height = 73
    Checkboxes = True
    Columns = <
      item
        Caption = 'Name'
        Width = 100
      end
      item
        Caption = 'Region address'
        Width = 100
      end
      item
        Caption = 'Begin Address'
        Width = 100
      end
      item
        Caption = 'End Address'
        Width = 100
      end
      item
        Caption = 'Location'
        Width = 500
      end>
    TabOrder = 4
    ViewStyle = vsReport
    OnChange = lvChange
    OnChanging = lvChanging
    OnClick = lvClick
  end
  object sbMultiLoad: TStatusBar
    Left = 0
    Top = 700
    Width = 799
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object btnScatFile1: TButton
    Left = 8
    Top = 2
    Width = 75
    Height = 17
    Caption = 'Scatter File 1'
    TabOrder = 6
    OnClick = btnScatFileClick
  end
  object btnScatFile2: TButton
    Tag = 1
    Left = 8
    Top = 20
    Width = 75
    Height = 17
    Caption = 'Scatter File 2'
    TabOrder = 7
    OnClick = btnScatFileClick
  end
  object lblScatFileName2: TStaticText
    Left = 88
    Top = 20
    Width = 665
    Height = 17
    AutoSize = False
    BorderStyle = sbsSunken
    Color = clSkyBlue
    ParentColor = False
    TabOrder = 8
  end
  object btnScatFile3: TButton
    Tag = 2
    Left = 8
    Top = 38
    Width = 75
    Height = 17
    Caption = 'Scatter File 3'
    TabOrder = 9
    OnClick = btnScatFileClick
  end
  object lblScatFileName3: TStaticText
    Left = 88
    Top = 38
    Width = 665
    Height = 17
    AutoSize = False
    BorderStyle = sbsSunken
    Color = clSkyBlue
    ParentColor = False
    TabOrder = 10
  end
  object btnScatFile4: TButton
    Tag = 3
    Left = 8
    Top = 56
    Width = 75
    Height = 17
    Caption = 'Scatter File 4'
    TabOrder = 11
    OnClick = btnScatFileClick
  end
  object lblScatFileName4: TStaticText
    Left = 88
    Top = 56
    Width = 665
    Height = 17
    AutoSize = False
    BorderStyle = sbsSunken
    Color = clSkyBlue
    ParentColor = False
    TabOrder = 12
  end
  object btnDelLoad4: TButton
    Tag = 3
    Left = 540
    Top = 648
    Width = 75
    Height = 25
    Caption = 'Delete Load 4 '
    TabOrder = 13
    OnClick = btnDelLoadClick
  end
  object btnDelLoad3: TButton
    Tag = 2
    Left = 456
    Top = 648
    Width = 75
    Height = 25
    Caption = 'Delete Load 3'
    TabOrder = 14
    OnClick = btnDelLoadClick
  end
  object btnDelLoad2: TButton
    Tag = 1
    Left = 364
    Top = 648
    Width = 75
    Height = 25
    Caption = 'Delete Load 2'
    TabOrder = 15
    OnClick = btnDelLoadClick
  end
  object btnDelLoad1: TButton
    Left = 272
    Top = 648
    Width = 75
    Height = 25
    Caption = 'Delete Load 1'
    TabOrder = 16
    OnClick = btnDelLoadClick
  end
  object lvPar1: TListView
    Left = 6
    Top = 144
    Width = 745
    Height = 65
    Checkboxes = True
    Columns = <
      item
        Caption = 'Parameter'
        Width = 100
      end
      item
        Caption = 'Information'
        Width = 700
      end>
    TabOrder = 17
    ViewStyle = vsReport
    OnChange = lvParamChange
    OnChanging = lvParamChanging
    OnClick = lvParamClick
  end
  object lvPar2: TListView
    Tag = 1
    Left = 6
    Top = 288
    Width = 745
    Height = 65
    Columns = <
      item
        Caption = 'Parameter'
      end
      item
        Caption = 'Information'
      end>
    TabOrder = 18
    ViewStyle = vsReport
    OnChange = lvParamChange
    OnChanging = lvParamChanging
  end
  object lvPar3: TListView
    Tag = 2
    Left = 6
    Top = 432
    Width = 745
    Height = 65
    Columns = <
      item
        Caption = 'Parameter'
      end
      item
        Caption = 'Information'
      end>
    TabOrder = 19
    ViewStyle = vsReport
    OnChange = lvParamChange
    OnChanging = lvParamChanging
  end
  object lvPar4: TListView
    Tag = 3
    Left = 6
    Top = 576
    Width = 745
    Height = 65
    Columns = <
      item
        Caption = 'Parameter'
      end
      item
        Caption = 'Information'
      end>
    TabOrder = 20
    ViewStyle = vsReport
    OnChange = lvParamChange
    OnChanging = lvParamChanging
  end
  object dlgOpenScatter1: TOpenDialog
    Filter = 'Scatter File (*.txt)|*.txt|All File (*.*)|*.*'
    Title = 'Open'
    Left = 576
  end
  object dlgOpenROM1: TOpenDialog
    Title = 'Open'
    Left = 576
    Top = 32
  end
  object dlgOpenFAT1: TOpenDialog
    Title = 'Open'
    Left = 576
    Top = 64
  end
  object dlgOpenScatter2: TOpenDialog
    Tag = 1
    Filter = 'Scatter File (*.txt)|*.txt|All File (*.*)|*.*'
    Title = 'Open'
    Left = 608
  end
  object dlgOpenScatter3: TOpenDialog
    Tag = 2
    Filter = 'Scatter File (*.txt)|*.txt|All File (*.*)|*.*'
    Title = 'Open'
    Left = 640
  end
  object dlgOpenScatter4: TOpenDialog
    Tag = 3
    Filter = 'Scatter File (*.txt)|*.txt|All File (*.*)|*.*'
    Title = 'Open'
    Left = 672
  end
  object dlgOpenROM2: TOpenDialog
    Tag = 1
    Title = 'Open'
    Left = 608
    Top = 32
  end
  object dlgOpenROM3: TOpenDialog
    Tag = 2
    Title = 'Open'
    Left = 640
    Top = 32
  end
  object dlgOpenROM4: TOpenDialog
    Tag = 3
    Title = 'Open'
    Left = 672
    Top = 32
  end
  object dlgOpenFAT2: TOpenDialog
    Tag = 1
    Title = 'Open'
    Left = 608
    Top = 64
  end
  object dlgOpenFAT3: TOpenDialog
    Tag = 2
    Title = 'Open'
    Left = 640
    Top = 64
  end
  object dlgOpenFAT4: TOpenDialog
    Tag = 3
    Title = 'Open'
    Left = 672
    Top = 64
  end
  object dlgOpenSecRo: TOpenDialog
    Title = 'Open SEC_RO file ...'
    Left = 600
    Top = 120
  end
  object m_dlgOpenGPS: TOpenDialog
    Title = 'Open GPS ROM'
    Left = 632
    Top = 120
  end
end
