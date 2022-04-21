#include "FileOpen.h"
#include "stdafx.h"
#include "InternalFrame.h"
#include "stdafx.h"
#include "Kernel.h"

namespace scv {

FileOpen::~FileOpen()
{
   delete[] path;
}

#if defined(_WIN32) || defined(WIN32)

void FileOpen::showDialog()
{
   /*path = NULL;

   HRESULT hResult = CoInitializeEx(NULL,
      COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

   if (SUCCEEDED(hResult))
   {
      //Create a instance to open the fileOpenDialog

      IFileOpenDialog *pFileOpen;

      hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL,
         CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileOpen));

      if (SUCCEEDED(hResult))
      {
         //show the File Open
         hResult = pFileOpen->Show(NULL);

         //get the file name result
         if (SUCCEEDED(hResult))
         {
            IShellItem *pItem;
            hResult = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hResult))
            {
               PWSTR FilePath;
               hResult = pItem->GetDisplayName(SIGDN_FILESYSPATH, &FilePath);

               //get the file name and copy to "path"
               if (SUCCEEDED(hResult))
               {
                  int count = wcslen(FilePath);
                  path = new char[2*count];
                  wcstombs(path, FilePath, count);
                  path[count] = '\0';
                  CoTaskMemFree(FilePath);

               }
               pItem->Release();
            }
         }
         pFileOpen->Release();
      }
      CoUninitialize();
   }*/
}
#else
void FileOpen::showDialog()
{
	std::cout << "Sorry, this is not implemented on linux yet =(" << std::endl;
	return;
}
#endif



std::string FileOpen::getFilePath()
{
   if(path != NULL) {
      std::string ret;
      ret.append(path);
      std::replace(ret.begin(),ret.end(), '\\' , '/' );
      return ret;
   } else {
      return "";
   }
}

} // namespace scv