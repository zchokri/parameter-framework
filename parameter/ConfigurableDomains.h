/* 
 * INTEL CONFIDENTIAL
 * Copyright © 2011 Intel 
 * Corporation All Rights Reserved.
 * 
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its suppliers
 * or licensors. Title to the Material remains with Intel Corporation or its
 * suppliers and licensors. The Material contains trade secrets and proprietary
 * and confidential information of Intel or its suppliers and licensors. The
 * Material is protected by worldwide copyright and trade secret laws and
 * treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or
 * disclosed in any way without Intel’s prior express written permission.
 * 
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel in writing.
 * 
 * CREATED: 2011-06-01
 * UPDATED: 2011-07-27
 */
#pragma once

#include "BinarySerializableElement.h"
#include <set>
#include <list>


class CParameterBlackboard;
class CConfigurableElement;
class CSyncerSet;
class CConfigurableDomain;
class CSelectionCriteriaDefinition;

class CConfigurableDomains : public CBinarySerializableElement
{
public:
    CConfigurableDomains();

    // Configuration/Domains handling
    /// Domains
    bool createDomain(const string& strName, string& strError);
    bool deleteDomain(const string& strName, string& strError);
    void deleteAllDomains();
    bool renameDomain(const string& strName, const string& strNewName, string& strError);
    bool setSequenceAwareness(const string& strDomain, bool bSequenceAware, string& strError);
    bool getSequenceAwareness(const string& strDomain, bool& bSequenceAware, string& strError) const;
    bool listDomainElements(const string& strDomain, string& strResult) const;
    bool split(const string& strDomain, CConfigurableElement* pConfigurableElement, string& strError);
    void listAssociatedElements(string& strResult) const;
    void listConflictingElements(string& strResult) const;
    void listDomains(string& strResult) const;
    /// Configurations
    bool listConfigurations(const string& strDomain, string& strResult) const;
    bool createConfiguration(const string& strDomain, const string& strConfiguration, const CParameterBlackboard* pMainBlackboard, string& strError);
    bool deleteConfiguration(const string& strDomain, const string& strConfiguration, string& strError);
    bool renameConfiguration(const string& strDomain, const string& strConfigurationName, const string& strNewConfigurationName, string& strError);
    bool restoreConfiguration(const string& strDomain, const string& strConfiguration, CParameterBlackboard* pMainBlackboard, bool bAutoSync, list<string>& lstrError) const;
    bool saveConfiguration(const string& strDomain, const string& strConfiguration, const CParameterBlackboard* pMainBlackboard, string& strError);
    bool setElementSequence(const string& strDomain, const string& strConfiguration, const vector<string>& astrNewElementSequence, string& strError);
    bool getElementSequence(const string& strDomain, const string& strConfiguration, string& strResult) const;
    bool setApplicationRule(const string& strDomain, const string& strConfiguration, const string& strApplicationRule, const CSelectionCriteriaDefinition* pSelectionCriteriaDefinition, string& strError);
    bool clearApplicationRule(const string& strDomain, const string& strConfiguration, string& strError);
    bool getApplicationRule(const string& strDomain, const string& strConfiguration, string& strResult) const;

    // Last applied configurations
    void listLastAppliedConfigurations(string& strResult) const;

    // Configurable element - domain association
    bool addConfigurableElementToDomain(const string& strDomain, CConfigurableElement* pConfigurableElement, const CParameterBlackboard* pMainBlackboard, string& strError);
    bool removeConfigurableElementFromDomain(const string& strDomain, CConfigurableElement* pConfigurableElement, string& strError);

    // Configuration Blackboard for element
    CParameterBlackboard* findConfigurationBlackboard(const string& strDomain,
                                     const string& strConfiguration,
                                     const CConfigurableElement* pConfigurableElement,
                                     uint32_t& uiBaseOffset,
                                     bool& bIsLastApplied,
                                     string& strError) const;

    // Binary settings load/store
    bool serializeSettings(const string& strBinarySettingsFilePath, bool bOut, uint8_t uiStructureChecksum, string& strError);

    // From IXmlSource
    virtual void toXml(CXmlElement& xmlElement, CXmlSerializingContext& serializingContext) const;

    // Ensure validity on whole domains from main blackboard
    void validate(const CParameterBlackboard* pMainBlackboard);

    // Configuration application if required
    void apply(CParameterBlackboard* pParameterBlackboard, CSyncerSet& syncerSet, bool bForce) const;

    // Class kind
    virtual string getKind() const;
private:
    // Returns true if children dynamic creation is to be dealt with
    virtual bool childrenAreDynamic() const;
    // Gather owned configurable elements owned by any domain
    void gatherAllOwnedConfigurableElements(set<const CConfigurableElement*>& configurableElementSet) const;
    // Domain retrieval
    CConfigurableDomain* findConfigurableDomain(const string& strDomain, string& strError);
    const CConfigurableDomain* findConfigurableDomain(const string& strDomain, string& strError) const;
};

