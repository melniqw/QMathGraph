#include "graphvertice.h"

GraphVertice::GraphVertice(const QString &name) :
    pressed(false), selected(false), pathSelected(false), name(name)
{
    setBackgroundColor();
    setBackgroundColorSelected();
    setBackgroundColorPressed();

    setPen();
    setPenSelected();
    setPenPressed();

    setPosition( QPointF(0,0) );
}

GraphVertice::~GraphVertice()
{
//    qDebug() << "~GraphVerticeSquare";
}

QRectF GraphVertice::boundingRect() const
{
    int width = name.length() * 7;
    int height = 40;

    return QRectF( QGraphicsItem::pos().x(), QGraphicsItem::pos().y(), width, height );
}

void GraphVertice::setName(const QString &name)
{
    this->name = name;
    update();
}

void GraphVertice::setPosition(const QPointF &pos)
{
//    position = pos;
    QGraphicsItem::setPos( pos.x(), pos.y() );
    update();
}

QPointF GraphVertice::getPosition() const
{
    return QGraphicsItem::pos();
}

void GraphVertice::setPen(const QPen &pen)
{
    regularPen = pen;
    update();
}

QPen GraphVertice::getPen() const
{
    return regularPen;
}

void GraphVertice::setPenSelected(const QPen &pen)
{
    selectedPen = pen;
    update();
}

QPen GraphVertice::getPenSelected() const
{
    return selectedPen;
}

void GraphVertice::setPenPressed(const QPen &pen)
{
    pressedPen = pen;
    update();
}

QPen GraphVertice::getPenPressed() const
{
    return pressedPen;
}

void GraphVertice::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    update();
}

QColor GraphVertice::getBackgroundColor() const
{
    return backgroundColor;
}

void GraphVertice::setBackgroundColorSelected(const QColor &color)
{
    backgroundColorSelected = color;
    update();
}

QColor GraphVertice::getBackgroundColorSelected() const
{
    return backgroundColorSelected;
}

void GraphVertice::setBackgroundColorPressed(const QColor &color)
{
    backgroundColorPressed = color;
    update();
}

QColor GraphVertice::getBackgroundColorPressed() const
{
    return backgroundColorPressed;
}

void GraphVertice::select(bool s)
{
    selected = s;
    update();
}

void GraphVertice::selectPath(bool s)
{
    pathSelected = s;
    update();
}

void GraphVertice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QBrush brush(backgroundColor);
    QPen pen;

    brush.setColor( backgroundColor );
    pen = regularPen;

    if ( selected )
    {
        brush.setColor( backgroundColorSelected );
        pen = selectedPen;
    }

    if ( pressed )
    {
        brush.setColor( backgroundColorPressed );
        pen = pressedPen;
    }

    if ( pathSelected )
    {
        pen.setWidth( pen.width() + 2 );
    }

    painter->setPen( pen );

    painter->fillRect( rect, brush );
    painter->drawRoundRect( rect, roundness(rect.width()), roundness(rect.height()) );

    painter->drawText( rect, Qt::AlignCenter, name );
}

void GraphVertice::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit verticeMoved( this, pos() );

    QGraphicsItem::mouseMoveEvent( event );
}

void GraphVertice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;

    update();
    QGraphicsItem::mousePressEvent( event );

    emit verticePressed( this );
}

void GraphVertice::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;

    update();
    QGraphicsItem::mouseReleaseEvent( event );

    emit verticeReleased( this );
}

void GraphVertice::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if ( selected )
    {
        selected = false;
        emit verticeUnselected( this );
    }
    else
    {
        emit verticeSelected( this );
    }

    QGraphicsItem::mouseDoubleClickEvent( event );
}

int GraphVertice::roundness(double size) const
{
    const int diameter = 15;
    return 100 * diameter / int(size);
}
