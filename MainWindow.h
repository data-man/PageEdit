/************************************************************************
**
**  Copyright (C) 2019 Kevin B. Hendricks, Stratford, Ontario, Canada
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_main.h"

#include <QtCore/QSignalMapper>
#include <QMap>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QMainWindow>
#include <Viewer.h>
#include <Inspector.h>

class WebViewEdit;
class Inspector;
class QWebEngineView;
class QVBoxLayout;
class QHBoxLayout;
class QSlider;
class QLabel;
class SelectCharacter;

const int STATUSBAR_MSG_DISPLAY_TIME = 7000;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString filepath, QWidget *parent = 0);
    ~MainWindow();
    QList<ElementIndex> GetCaretLocation();
    bool IsVisible();
    bool HasFocus();
    bool eventFilter(QObject *object, QEvent *event);
    void setMathJaxURL(QString mathjaxurl) { m_mathjaxurl = mathjaxurl; };
    void setUserCSSURL(QString usercssurl) { m_usercssurl = usercssurl; }

    // Zoom Related
    float GetZoomFactor();
    int   ZoomFactorToSliderRange(float zoom_factor);
    float SliderRangeToZoomFactor(int slider_range_value);
    void  ZoomByStep(bool zoom_in);
    void  ZoomByFactor(float new_zoom_factor);

public slots:

    // Zoom Related
    void ZoomIn();
    void ZoomOut();
    void ZoomReset();
    void SliderZoom(int slider_value);
    void UpdateZoomSlider(float new_zoom_factor);
    void UpdateZoomLabel(int slider_value);

    // General Slots
    void DoUpdatePage();
    void UpdatePage(const QString &filename);
    void ScrollTo(QList<ElementIndex> location);
    void SetZoomFactor(float factor);
    void LinkClicked(const QUrl &url);
    void EmitGoToPreviewLocationRequest();
    void InspectPreviewPage();
    void SelectAllPreview();
    void CopyPreview();
    void ReloadPreview();
    void ShowMessageOnStatusBar(const QString &message = "", int millisecond_duration = STATUSBAR_MSG_DISPLAY_TIME);

    // GUI slots
    void SelectEntryOnHeadingToolbar(const QString &element_name);
    void ApplyHeadingStyleToTab(const QString &heading_type);
    void SetPreserveHeadingAttributes(bool new_state);
    bool Save();
    void Open();
    void Exit();
    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void SelectAll();
    void Paste();
    void PasteText(const QString& text);
    void Preferences();
    void InsertSpecialCharacter();
    void InsertSGFSectionMarker();
    void InsertBulletedList();
    void InsertNumberedList();
    void Bold();
    void Italic();
    void Underline();
    void Strikethrough();
    void Subscript();
    void Superscript();
    void AlignLeft();
    void AlignCenter();
    void AlignRight();
    void AlignJustify();
    void DecreaseIndent();
    void IncreaseIndent();

signals:
    void Shown();
    void ZoomFactorChanged(float factor);
    void GoToPreviewLocationRequest();
    void RequestPreviewReload();

    /**
     * Emitted whenever m_WebView wants to open an URL.
     * @param url The URL to open.
     */
    void OpenUrlRequest(const QUrl &url);


protected:
    virtual void hideEvent(QHideEvent* event);
    virtual void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent * event);

private:
    void SetupView();
    void LoadSettings();
    void ConnectSignalsToSlots();
    void UpdateWindowTitle();

    const QMap<QString, QString> GetLoadFiltersMap();
    const QMap<QString, QString> GetSaveFiltersMap();

    WebViewEdit *m_WebView;
    Inspector *m_Inspector;
    QString m_Filepath;
    bool m_GoToRequestPending;
    bool m_MouseReleaseEventHappened;

    QString m_mathjaxurl;
    QString m_usercssurl;

    QSignalMapper *m_headingMapper;
    bool m_preserveHeadingAttributes;
    QString m_CurrentFilePath;
    SelectCharacter* m_SelectCharacter;
    QSlider *m_slZoomSlider;
    QLabel *m_lbZoomLabel;
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H