//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_SNIRRECEIVERBASE_H_
#define __INET_SNIRRECEIVERBASE_H_

#include "ReceiverBase.h"

namespace radio
{

class INET_API SNIRReceiverBase : public ReceiverBase
{
    protected:
        double snirThreshold;

    protected:
        virtual void initialize(int stage);

        virtual bool areOverlappingBands(Hz carrierFrequency1, Hz bandwidth1, Hz carrierFrequency2, Hz bandwidth2) const;

        /**
         * Returns the physical properties of the reception including noise and
         * signal related measures, error probabilities, actual error counts, etc.
         * Part of the reception process, see class comment.
         */
        virtual const RadioReceptionIndication *computeReceptionIndication(const IListening *listening, const IReception *reception, const std::vector<const IReception *> *interferingReceptions, const INoise *backgroundNoise) const;

        /**
         * Returns whether the reception is free of any errors. Part of the reception
         * process, see class comment.
         */
        virtual bool computeIsReceptionSuccessful(const IReception *reception, const RadioReceptionIndication *indication) const;

        virtual const INoise *computeNoise(const IListening *listening, const std::vector<const IReception *> *receptions, const INoise *backgroundNoise) const = 0;
        virtual double computeMinSNIR(const IReception *reception, const INoise *noise) const = 0;

    public:
        SNIRReceiverBase() :
            ReceiverBase(),
            snirThreshold(sNaN)
        {}

        virtual double getSNIRThreshold() const { return snirThreshold; }
        virtual const IReceptionDecision *computeReceptionDecision(const IListening *listening, const IReception *reception, const std::vector<const IReception *> *interferingReceptions, const INoise *backgroundNoise) const;
};

}

#endif
