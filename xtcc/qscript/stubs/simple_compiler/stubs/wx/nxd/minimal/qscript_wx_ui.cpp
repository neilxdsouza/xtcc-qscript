/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp 43915 2006-12-11 09:33:34Z CE $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
 
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
 
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
#if 0
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};
#endif /*  0 */

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------
// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,
    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// Define a new canvas which can receive some events
class MyImageCanvas: public wxScrolledWindow
{
  public:
    MyImageCanvas(wxWindow *parent, const wxPoint& pos, const wxSize& size, string p_filename)
	    : wxScrolledWindow(parent, wxID_ANY, pos, size),
	      img_filename (p_filename)
    {

    }
    ~MyImageCanvas(void){};
    string img_filename;
    wxBitmap my_jpeg;


    void OnPaint(wxPaintEvent& event);
DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyImageCanvas, wxScrolledWindow)
    EVT_PAINT(MyImageCanvas::OnPaint)
END_EVENT_TABLE()

void MyImageCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	wxString dir = wxT("./");
	wxBitmap bitmap( 100, 100 );
	wxImage image = bitmap.ConvertToImage();
	if ( !image.LoadFile( dir + _T("artichokes.jpeg")) )
		wxLogError(wxT("Can't load jpeg image"));
	else
		my_jpeg = wxBitmap(image);
        int x = 0, y = 0, yy = 100;
        dc.DrawBitmap(my_jpeg, x, y, true);


}








class MyQScriptCanvas;

// Define a new frame type: this is going to be our main frame
class MyQScriptFrame : public wxFrame
{
public:
    // ctor(s)
    MyQScriptFrame(const wxString& title);
    MyQScriptCanvas         *m_canvas;


    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyQScriptFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyQScriptFrame::OnQuit)
    EVT_MENU(Minimal_About, MyQScriptFrame::OnAbout)
END_EVENT_TABLE()

	struct QuestionView {
		wxBoxSizer * questionTextSizer_;
		wxBoxSizer * stubSizer_;
		wxStaticText * theQuestionText_;
		wxBoxSizer * questionViewContainer_;
		vector <wxRadioButton*> rbVec_;
		vector <wxCheckBox*> cbVec_;
		QuestionView() :
			questionTextSizer_ (0), stubSizer_(0), 
			theQuestionText_(0), questionViewContainer_(0)
		{ }
	};

	struct stub_info {
		string name;
		int code;
		bool is_other;
		stub_info (string p_name, int p_code, bool p_is_other):
			name (p_name), code(p_code), is_other(p_is_other)
		{ }
	};

	vector <stub_info> agree;
	vector <stub_info> gender;

	enum QuestionType { nq, rq };

	struct Question {
		string q_text;
		vector <stub_info> * vec_stub_ptr;
		QuestionType question_type;
		int no_mpn;
		Question (string p_q_text, vector <stub_info> * p_vec_stub_ptr, QuestionType p_question_type, int p_no_mpn):
			q_text(p_q_text), vec_stub_ptr(p_vec_stub_ptr), question_type(p_question_type), no_mpn(p_no_mpn)
		{ }
	};

	Question * q1, * q2, *q3;
	vector <Question*> question_vec;
	
void init_data()
{
	agree.push_back (stub_info ("Strongly agree", 5, false));
	agree.push_back (stub_info ("Agree", 4, false));
	agree.push_back (stub_info ("Neutral", 3, false));
	agree.push_back (stub_info ("Disagree", 2, false));
	agree.push_back (stub_info ("Strongly Disagree", 1, false));

	gender.push_back (stub_info ("Male", 1, false));
	gender.push_back (stub_info ("Female", 2, false));

	q1 = new Question ("Please state your agreement with", &agree, nq, 1);
	q2 = new Question ("Please state your Gender", &gender, nq, 1);
	q3 = new Question ("Please state your income", &agree, rq, 1);
			
	question_vec.push_back (q1);
	question_vec.push_back (q2);
	question_vec.push_back (q3);
}

	//struct stub_info agree [] = {
	//	{ string("Agree strongly"), 5},
	//	{ string("Agree "), 4},
	//	{ string("Neutral "), 3},
	//	{ string("Disagree "), 2},
	//	{ string("Disagree Strongly "), 1}
	//};


class MyQScriptCanvas: public wxScrolledWindow
{
public:
    MyQScriptCanvas() {}
    MyQScriptCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size );
    ~MyQScriptCanvas(){};
    //void OnPaint( wxPaintEvent &event );
    //void OnQueryPosition( wxCommandEvent &event );
    //void OnAddButton( wxCommandEvent &event );
    //void OnDeleteButton( wxCommandEvent &event );
    //void OnMoveButton( wxCommandEvent &event );
    //void OnScrollWin( wxCommandEvent &event );
    //void OnMouseRightDown( wxMouseEvent &event );
    //void OnMouseWheel( wxMouseEvent &event );

    wxButton *m_button;
    wxBoxSizer *topsizer;
    void DrawQuestions (vector<Question*> & p_question_vec);
    void DrawSingleAnswerStubs (Question* & p_q, QuestionView * & p_qv);
    void DrawStubs (Question* & p_q, QuestionView * & p_qv);
    vector <QuestionView *> currentQuestionView_;

    DECLARE_DYNAMIC_CLASS(MyQScriptCanvas)
    DECLARE_EVENT_TABLE()
};

void MyQScriptCanvas::DrawSingleAnswerStubs (Question* & p_q, QuestionView * & p_qv)
{
	cout << __PRETTY_FUNCTION__ << endl;
	p_qv->rbVec_.clear();
	vector<stub_info> & stub_info_vec = * p_q->vec_stub_ptr;
	p_qv->stubSizer_ = new wxBoxSizer (wxVERTICAL);
	for (int i=0; i < stub_info_vec.size(); ++i) {
		wxBoxSizer * this_stub_sizer = new wxBoxSizer (wxHORIZONTAL);
		wxRadioButton * rb = 0;
		if (i == 0) {
			rb = new wxRadioButton (this, wxID_ANY, wxString (stub_info_vec[i].name.c_str(), wxConvUTF8),
				wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
		} else {
			rb = new wxRadioButton (this, wxID_ANY, wxString (stub_info_vec[i].name.c_str(), wxConvUTF8)
				);
		}
		rb->SetValue (false);
		p_qv->rbVec_.push_back(rb);
		MyImageCanvas * img_cnv = new MyImageCanvas (this, wxPoint(0,0), wxSize (100, 100), "artichokes.jpeg");
		//wxImage * img = new wxImage (wxString("artichokes.jpeg", wxConvUTF8));
		this_stub_sizer->Add(img_cnv);
		this_stub_sizer -> Add (rb);
		p_qv->stubSizer_->Add (this_stub_sizer);
	}
}

void MyQScriptCanvas::DrawStubs (Question* & p_q, QuestionView * & p_qv)
{
	if (p_q->question_type == nq) {
		if (p_q->no_mpn == 1) {
			DrawSingleAnswerStubs (p_q, p_qv);
		} else {
			cout << "Unhanled stub type" << endl;
		}
	} else {
		cout << "Unhanled question type" << endl;
	}
}

void MyQScriptCanvas::DrawQuestions (vector<Question*> & p_question_vec)
{
	for (int i = 0; i < p_question_vec.size(); ++i) {
		QuestionView * qv = new QuestionView();
		qv->theQuestionText_ = new wxStaticText (this, -1, wxT("dummy"));
		qv->theQuestionText_ ->SetLabel( wxString (p_question_vec[i]->q_text.c_str(), wxConvUTF8));
		qv->questionTextSizer_ = new wxBoxSizer (wxHORIZONTAL);
		qv->questionTextSizer_->Add (qv->theQuestionText_);
		DrawStubs (p_question_vec[i], qv);
		topsizer->Add (qv->questionTextSizer_);
		if (qv->stubSizer_) {
			topsizer->Add (qv->stubSizer_);
		}
		currentQuestionView_.push_back(qv);
	}

}

MyQScriptCanvas::MyQScriptCanvas ( wxWindow *parent, wxWindowID id,
                    const wxPoint &pos, const wxSize &size )
	: wxScrolledWindow( parent, id, pos, size, wxSUNKEN_BORDER | wxTAB_TRAVERSAL, _T("QScript canvas") ),
	  m_button (0)
{
	cout << __PRETTY_FUNCTION__ << endl;
	SetScrollRate( 10, 10 );
	SetVirtualSize( 500, 1000 );
	topsizer = new wxBoxSizer( wxVERTICAL );
	SetSizer (topsizer);

	DrawQuestions (question_vec);
}

IMPLEMENT_DYNAMIC_CLASS(MyQScriptCanvas, wxScrolledWindow)

BEGIN_EVENT_TABLE(MyQScriptCanvas, wxScrolledWindow)
  //EVT_PAINT(                  MyCanvas::OnPaint)
  //EVT_RIGHT_DOWN(             MyCanvas::OnMouseRightDown)
  //EVT_MOUSEWHEEL(             MyCanvas::OnMouseWheel)
  //EVT_BUTTON( ID_QUERYPOS,    MyCanvas::OnQueryPosition)
  //EVT_BUTTON( ID_ADDBUTTON,   MyCanvas::OnAddButton)
  //EVT_BUTTON( ID_DELBUTTON,   MyCanvas::OnDeleteButton)
  //EVT_BUTTON( ID_MOVEBUTTON,  MyCanvas::OnMoveButton)
  //EVT_BUTTON( ID_SCROLLWIN,   MyCanvas::OnScrollWin)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
//BEGIN_EVENT_TABLE(MyQScriptFrame, wxFrame)
//    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
//    EVT_MENU(Minimal_About, MyFrame::OnAbout)
//END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    //MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));
    init_data();
	wxInitAllImageHandlers();
    MyQScriptFrame *frame = new MyQScriptFrame(_T("Minimal wxWidgets App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyQScriptFrame::MyQScriptFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR
    m_canvas = new MyQScriptCanvas( this, wxID_ANY, wxPoint(0,0), wxSize(100,100) );

}


// event handlers

void MyQScriptFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyQScriptFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("Welcome to %s!\n")
                    _T("\n")
                    _T("This is the minimal wxWidgets sample\n")
                    _T("running under %s."),
                    wxVERSION_STRING,
                    wxGetOsDescription().c_str()
                 ),
                 _T("About wxWidgets minimal sample"),
                 wxOK | wxICON_INFORMATION,
                 this);
}
