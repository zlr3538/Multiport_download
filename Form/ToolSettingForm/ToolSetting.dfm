object tool_setting: Ttool_setting
  Left = 428
  Top = 132
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Settings for Multiport Download Tool'
  ClientHeight = 326
  ClientWidth = 457
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
  object pc_setting_for_tool: TPageControl
    Left = 6
    Top = 8
    Width = 443
    Height = 281
    ActivePage = ts_FormatFAT
    MultiLine = True
    TabIndex = 0
    TabOrder = 0
    object ts_FormatFAT: TTabSheet
      Caption = 'Format FAT'
      object GroupBox_NOR_Flash_FAT: TGroupBox
        Left = 11
        Top = 15
        Width = 390
        Height = 97
        Caption = 'NOR Flash FAT'
        TabOrder = 0
        object Label_Begin_Address_NOR: TLabel
          Left = 18
          Top = 24
          Width = 95
          Height = 16
          Caption = 'Begin Address :'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_Length_NOR: TLabel
          Left = 19
          Top = 55
          Width = 43
          Height = 16
          Caption = 'Length:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_0x_NOR1: TLabel
          Left = 130
          Top = 24
          Width = 13
          Height = 16
          Caption = '0x'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_0x_NOR2: TLabel
          Left = 130
          Top = 56
          Width = 13
          Height = 16
          Caption = '0x'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label1_Hex_NOR1: TLabel
          Left = 274
          Top = 25
          Width = 24
          Height = 16
          Caption = 'Hex'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label1_Hex_NOR2: TLabel
          Left = 274
          Top = 57
          Width = 24
          Height = 16
          Caption = 'Hex'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Edit_Begin_Address_NOR: TEdit
          Left = 149
          Top = 21
          Width = 118
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          MaxLength = 8
          ParentFont = False
          TabOrder = 0
          Text = '00000000'
          OnKeyPress = On_Filter_Key_Press
        end
        object Edit_Length_NOR: TEdit
          Left = 149
          Top = 53
          Width = 118
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          MaxLength = 8
          ParentFont = False
          TabOrder = 1
          Text = '00000000'
          OnKeyPress = On_Filter_Key_Press
        end
      end
      object GroupBox_NAND_Flash_FAT: TGroupBox
        Left = 11
        Top = 128
        Width = 390
        Height = 97
        Caption = 'NAND Flash FAT'
        TabOrder = 1
        object Label_Begin_Address_NAND: TLabel
          Left = 20
          Top = 24
          Width = 95
          Height = 16
          Caption = 'Begin Address :'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_Length_NAND: TLabel
          Left = 21
          Top = 55
          Width = 43
          Height = 16
          Caption = 'Length:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_0x_NAND1: TLabel
          Left = 132
          Top = 24
          Width = 13
          Height = 16
          Caption = '0x'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label_0x_NAND2: TLabel
          Left = 132
          Top = 56
          Width = 13
          Height = 16
          Caption = '0x'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label1_Hex_NAND1: TLabel
          Left = 276
          Top = 25
          Width = 24
          Height = 16
          Caption = 'Hex'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label1_Hex_NAND2: TLabel
          Left = 276
          Top = 57
          Width = 24
          Height = 16
          Caption = 'Hex'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Edit_Begin_Address_NAND: TEdit
          Left = 151
          Top = 21
          Width = 118
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          MaxLength = 8
          ParentFont = False
          TabOrder = 0
          Text = '00000000'
          OnKeyPress = On_Filter_Key_Press
        end
        object Edit_Length_NAND: TEdit
          Left = 151
          Top = 53
          Width = 118
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          MaxLength = 8
          ParentFont = False
          TabOrder = 1
          Text = '00000000'
          OnKeyPress = On_Filter_Key_Press
        end
      end
    end
    object ts_ComPort: TTabSheet
      Caption = 'Com Port'
      ImageIndex = 1
      object comport_usb_comport: TGroupBox
        Left = 11
        Top = 15
        Width = 390
        Height = 98
        Caption = 'USB Com Port Setting'
        TabOrder = 1
        object comport_description: TLabel
          Left = 40
          Top = 52
          Width = 336
          Height = 32
          Caption = 
            'This is for USB download only.  Include One Station USB download' +
            ', and Two Station USB download.'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
      end
      object checkbox_disconnect_comport: TCheckBox
        Left = 32
        Top = 40
        Width = 273
        Height = 17
        Caption = 'Disconnect com port after USB download'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
    end
    object ts_Backup: TTabSheet
      Caption = 'Backup Calibration Data'
      ImageIndex = 2
      object gb_calibration_setting: TGroupBox
        Left = 11
        Top = 15
        Width = 390
        Height = 98
        Caption = 'Calibration Data Folder Naming'
        TabOrder = 0
        object checkbox_use_comport: TCheckBox
          Left = 21
          Top = 24
          Width = 337
          Height = 17
          Caption = 'Use Com port index as folder name'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = checkbox_use_comportClick
        end
      end
      object GroupBox1: TGroupBox
        Left = 11
        Top = 128
        Width = 390
        Height = 98
        Caption = 'Calibration Data Setting'
        TabOrder = 1
        object Label_calibrationSetting: TLabel
          Left = 40
          Top = 52
          Width = 337
          Height = 32
          Caption = 
            'This will take effect only when folder name is Random ID.  If fo' +
            'lder name is Com port index,  the data will be deleted.  '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
      end
      object checkbox_delete_calibration: TCheckBox
        Left = 32
        Top = 152
        Width = 337
        Height = 17
        Caption = 'Delete calibration data after restore (only for RID)'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 2
      end
    end
  end
  object setting_OK: TButton
    Left = 247
    Top = 295
    Width = 82
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 1
    OnClick = setting_OKClick
  end
  object setting_Cancel: TButton
    Left = 366
    Top = 295
    Width = 83
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = setting_CancelClick
  end
end
