object EFuseWriterViewer: TEFuseWriterViewer
  Left = 270
  Top = 112
  BorderStyle = bsSingle
  Caption = 'EFuseWriterViewer'
  ClientHeight = 692
  ClientWidth = 807
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
  object SettingFileDisplayLabel: TLabel
    Left = 16
    Top = 23
    Width = 66
    Height = 16
    Caption = 'SettingFile:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object LockFileDisplayLabel: TLabel
    Left = 16
    Top = 55
    Width = 54
    Height = 16
    Caption = 'LockFile:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object SettingFilePathLabel: TLabel
    Left = 104
    Top = 24
    Width = 577
    Height = 16
    AutoSize = False
    Caption = 'SettingFilePathLabel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object LockFilePathLabel: TLabel
    Left = 104
    Top = 56
    Width = 585
    Height = 16
    AutoSize = False
    Caption = 'LockFilePathLabel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object EfuseReaderComPort: TLabel
    Left = 310
    Top = 24
    Width = 73
    Height = 20
    Caption = 'COM Port:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 86
    Width = 793
    Height = 603
    ActivePage = EFuseSetting
    TabIndex = 0
    TabOrder = 0
    object EFuseSetting: TTabSheet
      Caption = 'EFuseSetting'
      object Common_ControlGroup: TGroupBox
        Left = 534
        Top = 2
        Width = 241
        Height = 126
        Caption = 'Common control'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Visible = False
        object Disable_USB_AutoDetect_Display_Label: TLabel
          Left = 22
          Top = 96
          Width = 127
          Height = 16
          Caption = 'USB_download_type'
        end
        object Disable_USB_AutoDetect_Label: TLabel
          Left = 224
          Top = 96
          Width = 7
          Height = 16
          Caption = '0'
        end
        object CheckBoxDisable_EMMC_boot: TCheckBox
          Left = 19
          Top = 23
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          BiDiMode = bdLeftToRight
          Caption = 'Disable_EMMC_boot'
          Checked = True
          ParentBiDiMode = False
          State = cbChecked
          TabOrder = 0
        end
        object CheckBoxDisable_NAND_boot: TCheckBox
          Left = 19
          Top = 48
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Disable_NAND_boot'
          TabOrder = 1
        end
        object CheckBoxDisable_NAND_boot_speedup: TCheckBox
          Left = 19
          Top = 73
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Disable_NAND_boot_speedup'
          TabOrder = 2
        end
      end
      object USB_ID_Group: TGroupBox
        Left = 6
        Top = 102
        Width = 241
        Height = 126
        Caption = 'USB ID'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Visible = False
        object LabelUSB_PID: TLabel
          Left = 115
          Top = 60
          Width = 57
          Height = 16
          Caption = 'USB_PID'
        end
        object LabelUSB_VID: TLabel
          Left = 115
          Top = 93
          Width = 57
          Height = 16
          Caption = 'USB_VID'
        end
        object USB_PID_Display: TLabel
          Left = 34
          Top = 58
          Width = 60
          Height = 16
          Caption = 'USB_PID:'
        end
        object USB_VIDDisplay: TLabel
          Left = 31
          Top = 93
          Width = 60
          Height = 16
          Caption = 'USB_VID:'
        end
        object CheckBoxEnable_ID: TCheckBox
          Left = 19
          Top = 25
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_ID'
          TabOrder = 0
        end
      end
      object SpareGroupBox: TGroupBox
        Left = 274
        Top = 101
        Width = 241
        Height = 127
        Caption = 'Spare'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        Visible = False
        object Labelspare_byte: TLabel
          Left = 111
          Top = 54
          Width = 68
          Height = 16
          Caption = 'spare_byte'
        end
        object Labelspare_data: TLabel
          Left = 112
          Top = 80
          Width = 71
          Height = 16
          Caption = 'spare data: '
        end
        object SpareDataDisplay: TLabel
          Left = 22
          Top = 80
          Width = 75
          Height = 16
          Caption = 'Spare Data: '
        end
        object SpareBytesDisplay: TLabel
          Left = 22
          Top = 53
          Width = 74
          Height = 16
          Caption = 'SpareBytes:'
        end
        object CheckBoxEnable_spare: TCheckBox
          Left = 19
          Top = 25
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_spare'
          TabOrder = 0
        end
      end
      object Security_controlGroupBox: TGroupBox
        Left = 535
        Top = 131
        Width = 241
        Height = 437
        Caption = 'Security control'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        Visible = False
        object CheckBoxEnable_ACC: TCheckBox
          Left = 19
          Top = 25
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_ACC'
          TabOrder = 0
        end
        object CheckBoxEnable_SBC: TCheckBox
          Left = 19
          Top = 51
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_SBC'
          TabOrder = 1
        end
        object CheckBoxEnable_DAA: TCheckBox
          Left = 19
          Top = 81
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_DAA'
          TabOrder = 2
        end
        object CheckBoxEnable_SLA: TCheckBox
          Left = 19
          Top = 108
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_SLA'
          TabOrder = 3
        end
        object CheckBoxEnable_ACK: TCheckBox
          Left = 18
          Top = 132
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_ACK'
          TabOrder = 4
        end
        object CheckBoxDisable_JTAG: TCheckBox
          Left = 18
          Top = 158
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Disable_JTAG'
          TabOrder = 5
        end
        object CheckBoxEnable_Root_Cert: TCheckBox
          Left = 18
          Top = 188
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_Root_Cert'
          TabOrder = 6
        end
      end
      object AC_keyGroupBox: TGroupBox
        Left = 6
        Top = 2
        Width = 509
        Height = 99
        Caption = 'AC key'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        object Labelac_key: TLabel
          Left = 96
          Top = 47
          Width = 385
          Height = 42
          AutoSize = False
          Caption = 'ac_key'
          WordWrap = True
        end
        object ACKeyDisplayLabel: TLabel
          Left = 22
          Top = 47
          Width = 44
          Height = 16
          Caption = 'ACKey:'
        end
        object CheckBoxEnable_ackey: TCheckBox
          Left = 19
          Top = 22
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_ackey'
          TabOrder = 0
        end
      end
      object SBC_public_keyGroupBox: TGroupBox
        Left = 6
        Top = 233
        Width = 509
        Height = 336
        Caption = 'SBC public key'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        Visible = False
        object Labelpublic_key_e: TLabel
          Left = 112
          Top = 52
          Width = 80
          Height = 16
          Caption = 'public_key_e'
          Visible = False
        end
        object Labelpublic_key_n: TLabel
          Left = 110
          Top = 79
          Width = 385
          Height = 250
          AutoSize = False
          Caption = 'public_key_n'
          Visible = False
          WordWrap = True
        end
        object PublicKeyEDisplayLabel: TLabel
          Left = 20
          Top = 55
          Width = 72
          Height = 16
          Caption = 'PublicKeyE:'
          Visible = False
        end
        object PublicKeyNDisplayLabel: TLabel
          Left = 20
          Top = 80
          Width = 73
          Height = 16
          Caption = 'PublicKeyN:'
          Visible = False
        end
        object SBC_PublicKey_Hash_Display_Label: TLabel
          Left = 20
          Top = 103
          Width = 95
          Height = 16
          Caption = 'PublicKeyHash:'
          Visible = False
        end
        object CheckBoxEnable_sbc_pubK_hash: TCheckBox
          Left = 19
          Top = 25
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Enable_sbc_pubK_hash'
          TabOrder = 0
        end
      end
    end
    object EFuseLock: TTabSheet
      Caption = 'EFuseLock'
      ImageIndex = 1
      object CommonRegisterLockSettingGroupBox: TGroupBox
        Left = 334
        Top = 3
        Width = 241
        Height = 134
        Caption = 'Common Register Lock Setting'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Visible = False
        object CheckBoxcom_ctrl_lock: TCheckBox
          Left = 19
          Top = 23
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          BiDiMode = bdLeftToRight
          Caption = 'com_ctrl_lock'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentBiDiMode = False
          ParentFont = False
          State = cbChecked
          TabOrder = 0
        end
        object CheckBoxusb_id_lock: TCheckBox
          Left = 19
          Top = 57
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'usb_id_lock'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object CheckBoxspare_lock: TCheckBox
          Left = 19
          Top = 94
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'spare_lock'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
      end
      object SecureLockSettingGroupBox: TGroupBox
        Left = 6
        Top = 3
        Width = 251
        Height = 134
        Caption = 'Secure Lock Setting'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Visible = False
        object CheckBoxsec_attr_lock: TCheckBox
          Left = 19
          Top = 47
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          BiDiMode = bdLeftToRight
          Caption = 'sec_attr_lock'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentBiDiMode = False
          ParentFont = False
          State = cbChecked
          TabOrder = 0
          Visible = False
        end
        object CheckBoxackey_lock: TCheckBox
          Left = 19
          Top = 15
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'ackey_lock'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          Visible = False
        end
        object CheckBoxsbc_pubk_hash_lock: TCheckBox
          Left = 19
          Top = 88
          Width = 214
          Height = 17
          Alignment = taLeftJustify
          Caption = 'sbc_pubk_hash_lock'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          Visible = False
        end
      end
    end
  end
  object com_port_number_ComboBox: TComboBox
    Left = 408
    Top = 16
    Width = 73
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 20
    ParentFont = False
    TabOrder = 1
    Text = 'com_port_number_ComboBox'
    Visible = False
    OnChange = com_port_number_ComboBoxChange
  end
end
