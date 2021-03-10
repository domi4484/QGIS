/***************************************************************************
  qgssettingsentry.cpp
  --------------------------------------
  Date                 : February 2021
  Copyright            : (C) 2021 by Damiano Lombardi
  Email                : damiano at opengis dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgssettingsentry.h"

#include "qgslogger.h"

QgsSettingsEntry::QgsSettingsEntry( QString key,
                                    QgsSettings::Section section,
                                    QVariant defaultValue,
                                    QString description )
  : mKey( key )
  , mDefaultValue( defaultValue )
  , mSection( section )
  , mDescription( description )
{
}

QgsSettingsEntry::~QgsSettingsEntry()
{
}

QString QgsSettingsEntry::key( const QString &dynamicKeyPart ) const
{
  if ( dynamicKeyPart.isEmpty() == false )
  {
    if ( hasDynamicKey() == false )
    {
      QgsLogger::warning( QStringLiteral( "Settings '%1' don't have a dynamic key, the provided dynamic key part will be ignored" ).arg( mKey ) );
      return mKey;
    }

    return mKey.arg( dynamicKeyPart );
  }
  else
  {
    if ( hasDynamicKey() == true )
      QgsLogger::warning( QStringLiteral( "Settings '%1' have a dynamic key but the dynamic key part was not provided" ).arg( mKey ) );

    return mKey;
  }
}

bool QgsSettingsEntry::hasDynamicKey() const
{
  return mKey.contains( "%1" );
}

QgsSettings::Section QgsSettingsEntry::section()
{
  return mSection;
}

bool QgsSettingsEntry::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  QgsSettings().setValue( key( dynamicKeyPart ),
                          value,
                          section() );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntry::settingsType() const
{
  return QgsSettingsEntry::Variant;
}

QVariant QgsSettingsEntry::valueFromPython() const
{
  return value<QVariant>();
}

QVariant QgsSettingsEntry::defaultValueFromPython() const
{
  return defaultValue<QVariant>();
}

QString QgsSettingsEntry::description() const
{
  return mDescription;
}

QgsSettingsEntryString::QgsSettingsEntryString( const QString &key,
    QgsSettings::Section section,
    const QString &defaultValue,
    const QString &description,
    int minLength,
    int maxLength )
  : QgsSettingsEntry( key,
                      section,
                      defaultValue,
                      description )
  , mMinLength( minLength )
  , mMaxLength( maxLength )
{

}

bool QgsSettingsEntryString::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( value.canConvert<QString>() == false )
  {
    QgsDebugMsg( QObject::tr( "Can't convert value '%1' to string for settings with key '%2'" )
                 .arg( value.toString() )
                 .arg( QgsSettingsEntry::key() ) );
    return false;
  }

  QString valueString = value.toString();
  if ( valueString.length() < mMinLength )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. String length '%2' is shorter than minimum length '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueString.length() )
                 .arg( mMinLength ) );
    return false;
  }

  if ( mMaxLength >= 0
       && valueString.length() > mMaxLength )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. String length '%2' is longer than maximum length '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueString.length() )
                 .arg( mMinLength ) );
    return false;
  }

  QgsSettingsEntry::setValue( value, dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryString::settingsType() const
{
  return QgsSettingsEntry::String;
}

int QgsSettingsEntryString::minLength()
{
  return mMinLength;
}

int QgsSettingsEntryString::maxLength()
{
  return mMaxLength;
}

QgsSettingsEntryStringList::QgsSettingsEntryStringList( const QString &key,
    QgsSettings::Section section,
    const QStringList &defaultValue,
    const QString &description )
  : QgsSettingsEntry( key,
                      section,
                      defaultValue,
                      description )
{

}

bool QgsSettingsEntryStringList::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( value.canConvert<QStringList>() == false )
  {
    QgsDebugMsg( QObject::tr( "Can't convert value '%1' to string list for settings with key '%2'" )
                 .arg( value.toString() )
                 .arg( QgsSettingsEntry::key() ) );
    return false;
  }

  QgsSettingsEntry::setValue( value, dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryStringList::settingsType() const
{
  return QgsSettingsEntry::StringList;
}

QgsSettingsEntryBool::QgsSettingsEntryBool( const QString &key,
    QgsSettings::Section section,
    bool defaultValue,
    const QString &description )
  : QgsSettingsEntry( key,
                      section,
                      defaultValue,
                      description )
{

}

bool QgsSettingsEntryBool::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( value.canConvert<bool>() == false )
  {
    QgsDebugMsg( QObject::tr( "Can't convert value '%1' to bool for settings with key '%2'" )
                 .arg( value.toString() )
                 .arg( QgsSettingsEntry::key() ) );
    return false;
  }

  QgsSettingsEntry::setValue( value, dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryBool::settingsType() const
{
  return QgsSettingsEntry::Bool;
}

QgsSettingsEntryInteger::QgsSettingsEntryInteger( const QString &key,
    QgsSettings::Section section,
    qlonglong defaultValue,
    const QString &description,
    qlonglong minValue,
    qlonglong maxValue )
  : QgsSettingsEntry( key,
                      section,
                      defaultValue,
                      description )
  , mMinValue( minValue )
  , mMaxValue( maxValue )
{

}

bool QgsSettingsEntryInteger::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( value.canConvert<qlonglong>() == false )
  {
    QgsDebugMsg( QObject::tr( "Can't convert value '%1' to qlonglong for settings with key '%2'" )
                 .arg( value.toString() )
                 .arg( QgsSettingsEntry::key() ) );
    return false;
  }

  qlonglong valueLongLong = value.toLongLong();
  if ( valueLongLong < mMinValue )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. Value '%2' is less than minimum value '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueLongLong )
                 .arg( mMinValue ) );
    return false;
  }

  if ( valueLongLong > mMaxValue )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. Value '%2' is greather than maximum value '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueLongLong )
                 .arg( mMinValue ) );
    return false;
  }

  QgsSettingsEntry::setValue( value, dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryInteger::settingsType() const
{
  return QgsSettingsEntry::Integer;
}

qlonglong QgsSettingsEntryInteger::minValue()
{
  return mMinValue;
}

qlonglong QgsSettingsEntryInteger::maxValue()
{
  return mMaxValue;
}

QgsSettingsEntryDouble::QgsSettingsEntryDouble( const QString &key,
    QgsSettings::Section section,
    double defaultValue,
    const QString &description,
    double minValue,
    double maxValue,
    double displayDecimals )
  : QgsSettingsEntry( key,
                      section,
                      defaultValue,
                      description )
  , mMinValue( minValue )
  , mMaxValue( maxValue )
  , mDisplayHintDecimals( displayDecimals )
{

}

bool QgsSettingsEntryDouble::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( value.canConvert<double>() == false )
  {
    QgsDebugMsg( QObject::tr( "Can't convert value '%1' to double for settings with key '%2'" )
                 .arg( value.toString() )
                 .arg( QgsSettingsEntry::key() ) );
    return false;
  }

  double valueDouble = value.toDouble();
  if ( valueDouble < mMinValue )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. Value '%2' is less than minimum value '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueDouble )
                 .arg( mMinValue ) );
    return false;
  }

  if ( valueDouble > mMaxValue )
  {
    QgsDebugMsg( QObject::tr( "Can't set value for settings with key '%1'. Value '%2' is greather than maximum value '%3'." )
                 .arg( QgsSettingsEntry::key() )
                 .arg( valueDouble )
                 .arg( mMinValue ) );
    return false;
  }

  QgsSettingsEntry::setValue( value, dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryDouble::settingsType() const
{
  return QgsSettingsEntry::Double;
}

double QgsSettingsEntryDouble::minValue() const
{
  return mMinValue;
}

double QgsSettingsEntryDouble::maxValue() const
{
  return mMaxValue;
}

int QgsSettingsEntryDouble::displayHintDecimals() const
{
  return mDisplayHintDecimals;
}

bool QgsSettingsEntryEnum::setValue( const QVariant &value, const QString &dynamicKeyPart )
{
  if ( mMetaEnum.isValid() == false )
  {
    QgsDebugMsg( QStringLiteral( "Invalid metaenum. Enum probably misses Q_ENUM or Q_FLAG declaration." ) );
    return false;
  }

  QgsSettingsEntry::setValue( mMetaEnum.valueToKey( value.toInt() ), dynamicKeyPart );
  return true;
}

QgsSettingsEntry::SettingsType QgsSettingsEntryEnum::settingsType() const
{
  return QgsSettingsEntry::Enum;
}
