#ifndef ERROR_CODE_H
#define ERROR_CODE_H

namespace ara::core 
{
/**
 * @brief Encapsulation of an error code.
 *
 * An ErrorCode contains a raw error code value and an error domain. The raw error code value is
 * specific to this error domain.
 * 
 * @req {SWS_CORE_00501}
 */
class ErrorCode final 
{


/**
 * @brief Construct a new ErrorCode instance with parameters
 *
 * This constructor does not participate in overload resolution unless EnumT is an enum type.
 * 
 * @param EnumT an enum type that contains error code values
 * @param e a domain-specific error code value
 * @param data optional vendor-specific supplementary error contextdata
 * 
 * @req {SWS_CORE_00512}
 */
 
template <typename EnumT>constexpr ErrorCode (EnumT e, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept;

/**
 * @brief Construct a new ErrorCode instance with parameters.
 * 
 * @param value a domain-specific error code value
 * @param domain a domain-specific error code value
 * @param data optional vendor-specific supplementary error contextdata
 * 
 * @req {SWS_CORE_00513}
 */
 
constexpr ErrorCode (ErrorDomain::CodeType value, ErrorDomain const&domain, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept;




/**
 * @brief Return the raw error code value.
 *
 * -
 * 
 * @return the raw error code value
 * 
 * @req {SWS_CORE_00514}
 */
constexpr ErrorDomain::CodeType Value () const noexcept;


/**
 * @brief Return the domain with which this ErrorCode is associated.
 *
 * 
 * @return the ErrorDomain
 * 
 * @req {SWS_CORE_00515}
 */
constexpr ErrorDomain::CodeType Value () const noexcept;




/**
 * @brief Return the supplementary error context data
 *
 * The underlying type and the meaning of the returned value are implementation-defined.
 * 
 * @return the supplementary error context data
 * 
 * @req {SWS_CORE_00516}
 */
constexpr ErrorDomain::SupportDataType SupportData () const noexcept;


/**
 * @brief Return a textual representation of this ErrorCode.
 *
 * 
 * @return the error message text
 * 
 * @req {SWS_CORE_00518}
 */
StringView Message () const noexcept;



/**
 * @brief Throw this error as exception.
 *
 * This function will determine the appropriate exception type for this ErrorCode and throw it. Thethrown exception will contain this ErrorCode
 *  
 * @req {SWS_CORE_00519}
 */
void ThrowAsException () const;

/**
 * @brief Global operator== for ErrorCode
 *
 * Two ErrorCode instances compare equal if the results of their Value() and Domain() functionsare equal. The result of SupportData() is not considered for equalit
 *  
 * @param lhs the left hand side of the comparison
 * @param rhs the right hand side of the comparison
 * 
 * @return true if the two instances compare equal, falseotherwise
 * 
 * @req {SWS_CORE_00571}
 */
constexpr bool operator== (ErrorCode const &lhs, ErrorCode const &rhs)noexcept;

/**
 * @brief Global operator!= for ErrorCode.
 *
 * Two ErrorCode instances compare equal if the results of their Value() and Domain() functionsare equal. The result of SupportData() is not considered for equalit
 *  
 * @param lhs the left hand side of the comparison
 * @param rhs the right hand side of the comparison
 * 
 * @return true if the two instances compare not equal, falseotherwise
 * 
 * @req {SWS_CORE_00572}
 */
constexpr bool operator!= (ErrorCode const &lhs, ErrorCode const &rhs)noexcept;

};


#endif // ERROR_CODE_H
