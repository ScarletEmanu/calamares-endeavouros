/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "MyPkgChooserQmlViewStep.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/Logger.h"
#include "utils/System.h"
#include "utils/Variant.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( MyPkgChooserQmlViewStepFactory, registerPlugin< MyPkgChooserQmlViewStep >(); )

MyPkgChooserQmlViewStep::MyPkgChooserQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
{
    emit nextStatusChanged( true );
}

QString
MyPkgChooserQmlViewStep::prettyName() const
{
    return m_config->prettyName();
}

QString
MyPkgChooserQmlViewStep::prettyStatus() const
{
    //QString option = m_pkgc;
    //return tr( "Install option: %1" ).arg( option );
    return m_config->prettyStatus();
}

bool
MyPkgChooserQmlViewStep::isNextEnabled() const
{
    return true;
}

bool
MyPkgChooserQmlViewStep::isBackEnabled() const
{
    return true;
}

bool
MyPkgChooserQmlViewStep::isAtBeginning() const
{
    return true;
}

bool
MyPkgChooserQmlViewStep::isAtEnd() const
{
    return true;
}

Calamares::JobList
MyPkgChooserQmlViewStep::jobs() const
{
    Calamares::JobList l;
    return l;
}

void
MyPkgChooserQmlViewStep::onLeave()
{
    m_config->updateGlobalStorage();
}

void
MyPkgChooserQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setDefaultId( moduleInstanceKey() );
    m_config->setConfigurationMap( configurationMap );
    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
}
