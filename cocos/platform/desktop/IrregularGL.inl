#if 0 
/// extended export methods list:
namespace cocos2d {
	namespace ext {
		void CC_DLL setGLSurfaceParent(HWND hwndParent);

		void CC_DLL setGLSurfaceNoB(bool nob = false, bool visible = false);

		void CC_DLL setGLSurfaceAlphaEnabled(bool alphaEnabled = false);

		void CC_DLL triggerMouseLeftRelease();

		void CC_DLL enableGdipCanvas(const char* iamgeSource);

		void CC_DLL changeGdipCanvas(const char* iamgeSource);
	}
}
#endif
/// use gdi+ to load png image, copy this whole code to any of your source code file.
/// this uitls must work with glfw3.1.1-mod by Link.Doex.
#ifndef _IRREGULARGL_
#define _IRREGULARGL_
#ifndef min
#define min(a,b) (a) < (b) ? (a) : (b)
#endif
#ifndef max
#define max(a,b) (a) > (b) ? (a) : (b)
#endif
#include <gdiplus.h>
#include <string>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") 

class IrregularGL
{
public:
	static IrregularGL* thisObject() {
		static IrregularGL theObject;
		return &theObject;
	}

	void setupGL(void)
	{
		glfwxSetBackgroundDriver(gdiplusLoadImage, gdiplusDrawImage, gdiplusUnloadImage);
	}

	void setBkgndSource(const wchar_t* image)
	{
		bkgndSource = image;
	}

	void reloadBkgnd(void)
	{
		gdiplusLoadImage();
	}

private:
	struct IrregularImpl
	{
		ULONG_PTR           gdiToken;
		GdiplusStartupInput gdiplusStartupInput;

		Gdiplus::Image*     image;
		ImageType           imageType;
		int                 imageWidth;
		int                 imageHeight;
		bool                bGdiplusReady;
	};

	std::wstring bkgndSource = L"background.png";
	static GLboolean gdiplusLoadImage(void** ppvImage = nullptr)
	{
		static IrregularImpl intri;
		if (!intri.bGdiplusReady) {
			intri.bGdiplusReady = (Gdiplus::Status::Ok == GdiplusStartup(&intri.gdiToken, &intri.gdiplusStartupInput, NULL));
		}

		if (!intri.bGdiplusReady)
			return GL_FALSE;

		if (intri.image != nullptr)
			delete intri.image;

		// do load image
		intri.image = Gdiplus::Image::FromFile(IrregularGL::thisObject()->bkgndSource.c_str());

		if (intri.image == nullptr) {
			return GL_FALSE;
		}

		intri.imageType = intri.image->GetType();
		intri.imageWidth = intri.image->GetWidth();
		intri.imageHeight = intri.image->GetHeight();

		if (ppvImage != nullptr)
			*ppvImage = &intri;

		return GL_TRUE;
	}

	static void gdiplusDrawImage(HDC hdc, void* ppvImage)
	{
		if (ppvImage == nullptr)
			return;

		IrregularImpl& intri = *(IrregularImpl*)ppvImage;
		if (intri.image != nullptr) {

			Graphics graph(hdc);

			Gdiplus::Point points[] = { Gdiplus::Point(0, 0),
				Gdiplus::Point(intri.imageWidth, 0),
				Gdiplus::Point(0, intri.imageHeight)
			};

			graph.DrawImage(intri.image, points, 3);
			graph.ReleaseHDC(hdc);
		}
	}

	static void gdiplusUnloadImage(void* ppvImage)
	{
		if (ppvImage == nullptr)
			return;

		IrregularImpl& intri = *(IrregularImpl*)ppvImage;
		if (intri.image)
			delete intri.image;

		if (intri.bGdiplusReady)
			GdiplusShutdown(intri.gdiToken);
	}
};

#undef min
#undef max

#endif /* _IRREGULARGL_ */
