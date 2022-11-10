#ifndef VCIRCULARPROGRESSBAR_H
#define VCIRCULARPROGRESSBAR_H

#include <QWidget>
#include <QStyle>
#include <QResizeEvent>
#include <QShowEvent>
#include <QFont>
namespace Ui {
class VCircularProgressBar;
}

class VCircularProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor )
    Q_PROPERTY(QString upperCaption READ upperCaption WRITE setUpperCaption )
    Q_PROPERTY(QString lowerCaption READ lowerCaption WRITE setLowerCaption )
    Q_PROPERTY(int progress READ progress WRITE setProgress )
    Q_PROPERTY(int minimun READ minimun WRITE setMinimun )
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum )
    Q_PROPERTY(bool isLoadingVisible READ isLoadingVisible WRITE setIsLoadingVisible )
    Q_PROPERTY(bool isShadowEnabled READ isShadowEnabled WRITE setIsShadowEnabled )
    Q_PROPERTY(QFont font READ font WRITE setFont )
public:
    VCircularProgressBar(QWidget *parent = 0);
    ~VCircularProgressBar();

    const QColor &color() const;
    void setColor(const QColor &newColor);

    const QString &upperCaption() const;
    void setUpperCaption(const QString &newUpperCaption);

    const QString &lowerCaption() const;
    void setLowerCaption(const QString &newLowerCaption);

    int progress() const;
    void setProgress(int newProgress);

    int minimun() const;
    void setMinimun(int newMinimun);

    int maximum() const;
    void setMaximum(int newMaximum);

    bool isLoadingVisible() const;
    void setIsLoadingVisible(bool newIsLoadingVisible);

    bool isShadowEnabled() const;
    void setIsShadowEnabled(bool newIsShadowEnabled);

    const QFont &font() const;
    void setFont(const QFont &newFont);


protected slots:
    void resizeEvent(QResizeEvent *ev);
    void showEvent(QShowEvent *ev);

private:
    Ui::VCircularProgressBar *ui;
    QColor _color;
    QString _upperCaption;
    QString _lowerCaption;
    int _progress;
    int _minimun;
    int _maximum;
    bool _isLoadingVisible;
    bool _isShadowEnabled;
    QFont _font;


private:    //methods
    void setShadow();
    void updateProgress();
    void reset();
    void updateFramesSize();


};

#endif // VCIRCULARPROGRESSBAR_H
