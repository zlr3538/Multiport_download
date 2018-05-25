//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mdt_component/error_handler/inc/GCTrace.h"

#include "form/mainform/MultiPortFlashDownloadTool.h"
#include "form/InputImageDlgForm/InputImageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmInputImage *frmInputImage;
//---------------------------------------------------------------------------
__fastcall TfrmInputImage::TfrmInputImage(TComponent* Owner)
        : TForm(Owner)
{
	this->m_p_CurrentHandle=NULL;
}

string TfrmInputImage::get_key_string(string key)
{
   string key_str;

   key_str =  "[" + key;
   key_str += "]          ";

   return key_str;
}

void TfrmInputImage::add_a_item_check_list_box(Image &img)
{
   string item = get_key_string(img.name) + img.path;

   clbRomImageSelector->Items->Add(item.c_str());

   clbRomImageSelector->Checked[clbRomImageSelector->Items->Count -1] = img.is_checked;

   if(img.name == "Ext_bootloader")
   {
      clbRomImageSelector->ItemEnabled[clbRomImageSelector->Items->Count -1] = false;
   }

}

string TfrmInputImage::get_key(string text)
{
   //step 1 -- get string in [XXX]
   return text.substr(text.find('[')+1, text.find(']')-text.find('[')-1);
}

void TfrmInputImage::update_image_path(int index, string new_path)
{

#if 0
   image_info *p_infos = &(*_p_image_infos->find(Caption.c_str())).second;

   (*p_infos)[index].path = new_path;

   string key = get_key(clbRomImageSelector->Items[0].Strings[index].c_str());

   string Item = get_key_string(key) + dlg_input_open_bin->FileName.c_str();

   clbRomImageSelector->Items[0].Strings[index]
                = Item.c_str();

   clbRomImageSelector->Refresh();
#else

#endif
}


void TfrmInputImage::set_image_info(map<string, MAUI_LoadHandle> &image_infos)
{
/*
	map<string, MAUI_LoadHandle>::iterator it_info;

	for(it_info = image_infos.begin();it_info != image_infos.end();it_info++)
	{
		cbScatterFileList->Items->Add((*it_info).first.c_str());
	}
*/
	_p_image_infos = &image_infos;

//	fill_rom_table(0);
}

void TfrmInputImage::fill_rom_table(int index)
{
    map<string, MAUI_LoadHandle>::iterator iter;
    MAUI_LoadHandle* LoadHandle=NULL;
    ROMSetting* romSetting=NULL;
    DL_HANDLE_T* p_dl_handle=NULL;
    unsigned short count=0;

try
{
		string scatter_file;

		clbRomImageSelector->Clear();

		cbScatterFileList->ItemIndex = index;

		scatter_file=cbScatterFileList->Items[0].Strings[index].c_str();

		if(NULL==_p_image_infos)
		{
			GC_TRACE("TfrmInputImage::fill_rom_table==>_p_image_infos is NULL");
			throw string("Pointer: _p_image_infos is NULL");
		}
		iter=_p_image_infos->find(scatter_file);
		if(iter==_p_image_infos->end())
		{
			GC_TRACE("TfrmInputImage::fill_rom_table==>scatter_file: %s",scatter_file.c_str());
			throw string("Can not find scatter file in _p_image_infos.");
		}
		romSetting=&(iter->second.m_romSetting);
		p_dl_handle=iter->second.m_dl_handle;
		if((NULL==romSetting)||(NULL==p_dl_handle))
		{
			GC_TRACE("Invalid MAUI_LoadHandle,romSetting:%d, p_dl_handle:%d",romSetting,p_dl_handle);
			throw string("Invalid MAUI_LoadHandle");
		}
		m_p_CurrentHandle=p_dl_handle;
		GC_TRACE("TfrmInputImage::fill_rom_table==>Dl Hanlde: 0x%08X",m_p_CurrentHandle);

		DL_INFO_EX Dl_Info;
		DL_GetInfo_Ex(*m_p_CurrentHandle,&Dl_Info);
		if(Dl_Info.brom_usb_supported)
		{
			this->ImageBootROMUSBDownload->Visible=true;
			this->ImageBootloaderUSBDownloadSupport->Visible=false;
		}
		else if(Dl_Info.bootloader_usb_supported)
		{
			this->ImageBootloaderUSBDownloadSupport->Visible=true;
			this->ImageBootROMUSBDownload->Visible=false;
		}
		else	//May be old load
		{
			this->ImageBootloaderUSBDownloadSupport->Visible=false;
			this->ImageBootROMUSBDownload->Visible=false;
		}

    if ( (S_DONE == DL_GetCount_Ex(*p_dl_handle, &count)) && (0 < count) )
		{
        ROM_INFO_EX romInfoEx[MAX_LOAD_SECTIONS] = { 0 };
        string Temp_FileName,Temp_FilePath,Temp_DisplayPath;
        if( !DL_Rom_GetInfoAll_Ex(*p_dl_handle, romInfoEx, MAX_LOAD_SECTIONS) )
        {
            for ( int i=0; i < count; i++ )
            {
                Temp_FileName=romInfoEx[i].name;
                Temp_FilePath=romInfoEx[i].filepath;
                Temp_DisplayPath=Temp_FileName+"   "+Temp_FilePath;
                clbRomImageSelector->Items->Add(Temp_DisplayPath.c_str());
                clbRomImageSelector->Checked[clbRomImageSelector->Items->Count -1] = romInfoEx[i].enable;

                if(!strncmp(romInfoEx[i].name,"Ext_bootloader",strlen("Ext_bootloader")))
                {
                    clbRomImageSelector->ItemEnabled[clbRomImageSelector->Items->Count -1] = false;
                }
            }
        }
        else
        {
            throw string("DL_Rom_GetInfoAll_Ex Error");
        }
    }
		else
		{
			throw string("DL_GetCount_Ex Error");
		}

		cbScatterFileList->Refresh();
	}
	catch(string &e)
	{
		throw ;
	}

}

int TfrmInputImage::get_rom_index(string name)
{
     for(int i=0; i<MAX_LOAD_SECTIONS; i++)
     {
         if(strcmp(name.c_str(), m_p_rom_info_array[i].name) == 0)
         {
            return i;
         }
     }

     GC_TRACE("TfrmInputImage::get_rom_index, Can't find ROM name in ROM array");
     return -1;
}

//---------------------------------------------------------------------------
//When user click value
void __fastcall TfrmInputImage::mbCancelClick(TObject *Sender)
{
    this->Close();
    this->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInputImage::mbOKClick(TObject *Sender)
{
    //Check is all ROM have been selected
    this->Close();
    this->ModalResult = mrOk;
}

//---------------------------------------------------------------------------
void __fastcall TfrmInputImage::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
   CanClose = true;
}


//---------------------------------------------------------------------------

void __fastcall TfrmInputImage::clbRomImageSelectorDblClick(
      TObject *Sender)
{
	int mtk_status;
	try
	{
		string BinaryFileName;
		string Exception_String;

	    if(!dlg_input_open_bin->Execute())
	    {
	        return;
	    }

		  BinaryFileName=dlg_input_open_bin->FileName.c_str();
	    if(!FileExists(dlg_input_open_bin->FileName))
	    {
			throw string("The requested file does not exist.");
	    }
		if(NULL==m_p_CurrentHandle)
		{
			throw string("Current DL Handle is NULL");
		}

		GC_TRACE("clbRomImageSelectorDblClick:==>Hanlde: 0x%08X Index: %d File Name: %s",m_p_CurrentHandle,clbRomImageSelector->ItemIndex,BinaryFileName.c_str());

	    //Update image path
		clbRomImageSelector->Items[0].Strings[clbRomImageSelector->ItemIndex]= BinaryFileName.c_str();

		if(S_DONE!=(mtk_status=DL_Rom_Unload_Ex(*m_p_CurrentHandle,clbRomImageSelector->ItemIndex)))
		{
			Exception_String=StatusToString(mtk_status);
			throw string("DL_Rom_Unload_Ex"+Exception_String);
		}

		if(S_DONE!=(mtk_status=DL_Rom_Load_Ex(*m_p_CurrentHandle,clbRomImageSelector->ItemIndex,BinaryFileName.c_str())))
		{
			Exception_String=StatusToString(mtk_status);
			throw string("DL_Rom_Load_Ex"+Exception_String);
		}

		clbRomImageSelector->Refresh();
	}
	catch(string& e)
	{
		throw e;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInputImage::cbScatterFileListChange(TObject *Sender)
{
    fill_rom_table(cbScatterFileList->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TfrmInputImage::clbRomImageSelectorClickCheck(
      TObject *Sender)
{
#if 0
	//Get image list vector
	image_info *p_infos = &(*_p_image_infos->find(this->Caption.c_str())).second;
	int index = clbRomImageSelector->ItemIndex;

	if(index < 0)
	{
	return;
	}

	if( (unsigned int)index <= p_infos->size()-1 )
	{
	(*p_infos)[index].is_checked = clbRomImageSelector->Checked[index];

	if(   "Bootloader" == (*p_infos)[index].name
	 && "Ext_bootloader" == (*p_infos)[index+1].name)
	{
	 (*p_infos)[index+1].is_checked = clbRomImageSelector->Checked[index];
	 clbRomImageSelector->Checked[index+1] = clbRomImageSelector->Checked[index];
	}
	}
#else

	try
	{
		if(NULL==m_p_CurrentHandle)
		{
			GC_TRACE("TfrmInputImage::clbRomImageSelectorClickChec==>Current DL Hanlde is NULL");
			throw string("Current DL Hanlde is NULL");
		}
		DL_Rom_SetEnableAttr_Ex(*m_p_CurrentHandle, clbRomImageSelector->ItemIndex, clbRomImageSelector->Checked[clbRomImageSelector->ItemIndex]?_TRUE:_FALSE);
		GC_TRACE("Change Select Item:Handle:0x%08X Index: %d Checked?==%d",m_p_CurrentHandle,clbRomImageSelector->ItemIndex,clbRomImageSelector->Checked[clbRomImageSelector->ItemIndex]);

	}
	catch(std::string &e)
	{
		throw e;
	}

#endif

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfrmInputImage::FormShow(TObject *Sender)
{
	map<string, MAUI_LoadHandle>::iterator iter;
	cbScatterFileList->Clear();

	try
	{
		if(NULL==_p_image_infos)
		{
			throw string("Pointer _p_image_infos is NULL");
		}
		if(0==_p_image_infos->size())
		{
			throw string("0 Images Load");
		}
		for(iter=_p_image_infos->begin();iter!=_p_image_infos->end();iter++)
		{
			cbScatterFileList->Items->Add((*iter).first.c_str());
		}
		fill_rom_table(0);
	}
	catch(std::string &e)
	{
		Application->MessageBox(e.c_str(),"MDT Exception",MB_ICONERROR);
		return;
	}
}
//---------------------------------------------------------------------------

